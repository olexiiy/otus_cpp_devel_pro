#ifndef TIMER_H
#define TIMER_H
#include <chrono>
#include <iostream>
#include <random>
#include <sstream>

namespace myfunc {
    template <typename T>
    inline std::string ToString(const T& tX)
    {
        std::ostringstream oStream;
        oStream << tX;
        return oStream.str();
    }

    template <typename T>
    inline bool FromString(const std::string& sString, T& tX)
    {
        std::istringstream iStream(sString);
        return (iStream >> tX) ? true : false; // витягуємо значення в tX, повертаємо true (якщо вдало) або false (якщо невдало)
    }
}
class Timer {
private:
    // Псевдонимы типов используются для удобного доступа к вложенным типам
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<clock_t> m_beg;

public:
    Timer();

    void reset();

    double elapsed_ms() const;

    double elapsed_ml() const;

    void print_sec();

    void print_milli();

    void print_micro();
};

void ignoreLine();

template <typename T> // оголошення параметра шаблону функції
T getSMTH(const std::string_view& sv = "")
{

    while (true) // цикл продолжается до тех пор, пока пользователь не введёт корректное значение
    {
        std::cout << sv;
        T x;
        std::cin >> x;

        // Check for failed extraction
        if (!std::cin) // has a previous extraction failed?
        {
            // yep, so let's handle the failure
            std::cin.clear(); // put us back in 'normal' operation mode
            ignoreLine(); // and remove the bad input
            std::cerr << "Oops, that input is invalid.  Please try again.\n";
        }
        else {
            ignoreLine(); // remove any extraneous input
            return x;
        }
    }
}

template <typename S> // оголошення параметра шаблону функції
S getRandomNumber(S min = std::numeric_limits<S>::min(), S max = std::numeric_limits<S>::max())
{

    std::random_device device; // для получения зерна лучше чем от time(NULL)
    std::mt19937 mersenne(device()); // инициализируем Вихрь Мерсенна стартовым
    // числом

    std::uniform_int_distribution<> distribution(
        min, max); // Равномерное распределение [10, 20]

    const S randomNumber = static_cast<S>(distribution(mersenne));
    // генерируем случайное число в заданом диапазоне

    return randomNumber;
    // возвращаем случайное число в заданом диапазоне
}

std::string get_string(const std::string_view& sv);

bool playAgain();

template <typename S> // оголошення параметра шаблону функції
S getRandomNumber(S min, S max);

bool approximatelyEqualAbsRel(double a, double b, double absEpsilon = 0.000000000001, double relEpsilon = 0.00000001);

#endif // TIMER_H
