#include <iostream>

#include "tasks.h"
#include "tasks.cpp"

int main() {

    // std::cout << math::fibonacci(0) << std::endl;
    // std::cout << math::fibonacci(5) << std::endl;
    // std::cout << math::fibonacci(10) << std::endl;

    // std::cout << strutils::camel_to_snake("fooBarBaz") << std::endl;
    // std::cout << strutils::camel_to_snake("foo") << std::endl;
    // std::cout << strutils::camel_to_snake("") << std::endl;

    // uint32_t result = 4;
    // std::cout << strutils::parse_uint("", result) << " " << result << std::endl;
    // std::cout << strutils::parse_uint("4294967295", result) << " " << result << std::endl;
    // std::cout << strutils::parse_uint("123456789 x", result) << " " << result << std::endl;

    std::vector<uint8_t> input{
                0b01001100,
                0b11000011,
                0b10101101,
                0b01100010,
                0b11000011,
                0b10101101,
                0b00100000,
                0b01110011,
                0b01100101,
                0b00100000,
                0b01110100,
                0b01101001,
                0b00100000,
                0b01000011,
                0b00101011,
                0b00101011,
                0b00111111,
                0b00100000,
                0b11110000,
                0b10011111,
                0b10011000,
                0b10000000
        };
        size_t result = std::numeric_limits<size_t>::max();

        std::cout << strutils::validate_utf8(input, result) << " " << result << std::endl;

    return 0;
}
