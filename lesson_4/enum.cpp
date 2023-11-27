#include <iostream>


namespace motivation {
    enum Alphabet {
        a, b, c
    };

    void func(Alphabet ) {
    }

    void func2(int ) {
    }

    void example() {
        Alphabet value = Alphabet::a; // it works. nice!
        Alphabet value2 = a; // it works also. bad :(

        func(value); // it works
        func2(value); // it works also
    }





    struct GoodAlphabet {
        enum {
            d = 1, e = 2, f = 3
        };
    };

    void example2() {
        auto d = GoodAlphabet::d;
        // hm... we can't name a type?
        int value = 2;
        switch(value) {
            case GoodAlphabet::d:
                std::cout << "d" << std::endl;
                break;
            case GoodAlphabet::e:
                std::cout << "e" << std::endl;
                break;
            case GoodAlphabet::f:
                std::cout << "f" << std::endl;
                break;
            default:
                break;
        }
    }
}

namespace basics {

    enum class Digit : uint64_t {
        one = 1, 
        two = 193, 
        three = 247
    };

    void func(Digit ) {

    }

    void func2(int ) {

    }

    void example() {
        // Digit value = one; // Compile error
        Digit value = Digit::one;

        func(value); // it works
        // func2(value); // Compile error
        func2(static_cast<int>(value)); // it works
    }
}

namespace advanced {

    namespace {
        enum Alphabet {
            a, b, c
        };
    }

    void func(Alphabet ) {
    }

    void func2(int ) {
    }

    void example() {
        Alphabet value = Alphabet::a; // it works
        Alphabet value2 = a; // it works also

        func(value); // it works
        func2(value); // it works also
    }


    namespace constants {
        enum Flag {
            d, e, f
        };
    }

    void example2() {
        constants::Flag value = constants::Flag::d; // it works
        constants::Flag value2 = constants::d; // it works also
        // constants::Flag value2 = d; // it does not work
    }
}

int main(int, char *[]) {

    motivation::example();

    basics::example();

    advanced::example();

    return 0;
}