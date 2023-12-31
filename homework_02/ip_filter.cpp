#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include "timer.h"
#include <algorithm>

#define UNUSED(arg) ((void)(arg))

#include "cmath"
#include <climits>
// Time Complexity O(n+k)// Space Complexity O(k)

std::vector<int> sort(std::vector<int> arr) {
    std::vector<int> items(arr.size());
    int min = INT_MAX;
    int max = INT_MIN;
    for (int x: arr) {
        if (x > max) max = x;
        if (x < min) min = x;
    }

    std::vector<int> counts(max - min + 1, 0);

    for (int x: arr) {
        counts[x - min]++;
    }

    int total = 0;
    for (int i = min; i <= max; i++) {
        int oldCount = counts[i - min];
        counts[i - min] = total;
        total += oldCount;
    }

    for (int x: arr) {
        items[counts[x - min]] = x;
        counts[x - min]++;
    }
    return items;
}


// about 4 seconds
// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d) {
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

class Ip_adress {
    std::vector<uint8_t> ip{};

    void push(const std::vector<std::string> &ip_s) {
        for (std::vector<std::string>::const_iterator ips_part = ip_s.cbegin(); ips_part != ip_s.cend(); ++ips_part) {
            ip.push_back(stoi(*ips_part));
        }
    };
public:
    Ip_adress(const std::vector<std::string> &ip_s) {
        ip.reserve(4);
        push(ip_s);
    };

    void ip_out() const {

        for (std::vector<uint8_t>::const_iterator ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part) {
            if (ip_part != ip.cbegin())
                std::cout << ".";
            std::cout << +(*ip_part);
        }
    }

    friend bool operator<(const Ip_adress &ip1, const Ip_adress &ip2) {
        return ip1.ip < ip2.ip;
    }

    const std::vector<uint8_t> &ip_get() const {

        return ip;
    }

    auto cbegin() const {
        return ip.cbegin();
    }

    auto cend() const {
        return ip.cend();
    }
};

void filter(const std::vector<Ip_adress> &ip_pool, uint8_t ip0) {
    for (std::vector<Ip_adress>::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
        if (ip->ip_get()[0] == ip0) {
            ip->ip_out();
            std::cout << "\n";
        }
    }
}

void filter(const std::vector<Ip_adress> &ip_pool, uint8_t ip0, uint8_t ip1) {
    for (std::vector<Ip_adress>::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
        if ((ip->ip_get()[0] == ip0) && (ip->ip_get()[1] == ip1)) {
            ip->ip_out();
            std::cout << "\n";
        }
    }
}

void filter_any(const std::vector<Ip_adress> &ip_pool, uint8_t) {
    for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
        auto it = std::find(ip->cbegin(), ip->cend(), 46);
        if (it != (ip->ip_get().cend())) {
            ip->ip_out();
            std::cout << "\n";
        }
    }
}

int main(int argc, char const *argv[]) {
    try {
        std::vector<Ip_adress> ip_pool;

        for (std::string line; std::getline(std::cin, line);) {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.rbegin(), ip_pool.rend());


        Timer t;
        {

//            sort(ip_pool);
        }
//        t.print_milli();


        for (std::vector<Ip_adress>::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
            ip->ip_out();
            std::cout << "\n";
        }

//        std::cout << "main thread id is " << std::this_thread::get_id() << std::endl;
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
        filter(ip_pool, 1);
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        filter(ip_pool, 46, 70);
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        filter_any(ip_pool, 46);

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    UNUSED(argv);
    UNUSED(argc);

    return 0;
}
