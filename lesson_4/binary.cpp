#include <iostream>

int main() {
    int value = 1'234'567; // dec (1234567)
    int value2 = 0xff;     // hex (255)
    int value3 = 0b1111;   // binary (15)
    int value4 = 0137;     // oct (95)

    std::cout << "0b10101010 = " << 0b10101010 << std::endl;

    std::cout << "0b01010101 = " << 0b01010101 << std::endl;

    std::cout << "0b11111111 = " << 0b11111111 << std::endl;

    std::cout << "(int8_t)0b11100000 = " << (int8_t)0b11100000 << std::endl;
    std::cout << "+(int8_t)0b11100000 = " << +(int8_t)0b11100000 << std::endl;

    std::cout << "0b10000000u = " << 0b10000000u << std::endl;

    std::cout << "+(int8_t)0b10000000 = " << +(int8_t)0b10000000ul << std::endl;

    return 0;
}