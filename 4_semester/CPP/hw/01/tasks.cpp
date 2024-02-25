#include "tasks.h"

int math::fibonacci(int n){
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

std::string strutils::camel_to_snake(std::string input){
    int length = input.length();
    std::string result = "";

    for (int i = 0; i < length; i++){
        if (input[i] >= 'a' && input[i] <= 'z'){
            result += input[i];
        }
        else if (input[i] >= 'A' && input[i] <= 'Z'){
            if (i != 0) result += '_';
            result += input[i] + 32;
        }
    }

    return result;
}

bool strutils::parse_uint(std::string input, uint32_t &result){
    if (input.length() == 0) return false;
    
    uint32_t max = std::numeric_limits<uint32_t>::max();
    uint32_t tmp_res = 0;

    for(char c : input){
        if (c < '0' || c > '9') return false;
        else {
            int tmp_digit = c - '0';

            if (tmp_res > (max - tmp_digit) / 10) {
                return false;
            }

            tmp_res = tmp_res * 10 + tmp_digit;
        }
    }

    result = tmp_res;
    return true;
}

bool strutils::validate_utf8(std::vector<uint8_t> input, size_t &result){
    size_t steps = 0;
    size_t output = 0;

    for(uint8_t number : input){
        if((number & 0b10000000) == 0b00000000){
            output++;
        }
        else if((number & 0b11100000) == 0b11000000){
            steps = 1;
        }
        else if((number & 0b11110000) == 0b11100000){
            steps = 2;
        }
        else if((number & 0b11111000) == 0b11110000){
            steps = 3;
        }
        else {
            return false;
        }
        for(size_t i = 1; i <= steps; ++i){
            if(output + i >= input.size()) return false;
            if((input[output + i] & 0b11000000) != 0b10000000) return false;
        }
        output += steps;
    }

    result = output;
    return true;
}
