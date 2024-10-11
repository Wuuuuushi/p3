#include "Wordset.hpp"
#include <string>
#include <iostream>

namespace shindler::ics46::project3 {

// returns s, as a number in the given base, mod the given modulus
size_t polynomialHashFunction(const std::string &string, unsigned int base,
                              unsigned int mod) {
    size_t hashValue{0}; //Set our return value to zero
    for (size_t i{0}; i < string.length(); i++)
    {
        size_t tmp_hashValue{0}; // Temporary value that will be used to store the value of each iteration resets after each iteration
        tmp_hashValue += (string[i] - 'a') + 1;
        for (size_t index{1}; index < string.length() - i; index++)
        {
            tmp_hashValue = tmp_hashValue * base;
        }
        hashValue += tmp_hashValue % mod;
    }
    return hashValue % mod;
}

}  // namespace shindler::ics46::project3
