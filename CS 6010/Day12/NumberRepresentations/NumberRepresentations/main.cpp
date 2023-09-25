//
//  main.cpp
//  NumberRepresentations
//
//  Created by Tailang  Cao on 9/6/23.
//

#include <iostream>
#include <cstdint>
#include <cmath>
#include <iomanip>
#include "function.hpp"

int main(int argc, const char * argv[]) {
    
    int x[] = { 7, 2, -56, 32, 1, 7, -2, 7 };
    std::cout << "size: " << sizeof(x) << "\n";//the size is 32, because have 8 bits.
    
    
    std::cout << "Size of uint8_t: " << sizeof(uint8_t) << " bytes" << std::endl;
    std::cout << "Size of uint16_t: " << sizeof(uint16_t) << " bytes" << std::endl;
    std::cout << "Size of uint64_t: " << sizeof(uint64_t) << " bytes" << std::endl;
    
    std::cout << "Size of int8_t: " << sizeof(int8_t) << " bytes" << std::endl;
    std::cout << "Size of int16_t: " << sizeof(int16_t) << " bytes" << std::endl;
    std::cout << "Size of int64_t: " << sizeof(int64_t) << " bytes" << std::endl;
    
    
    // Unsigned integer types
    uint8_t min_uint8 = 0;
    uint8_t max_uint8 = 0xFF;  // 8 bits set to 1
    
    uint16_t min_uint16 = 0;
    uint16_t max_uint16 = 0xFFFF;  // 16 bits set to 1
    
    uint64_t min_uint64 = 0;
    uint64_t max_uint64 = 0xFFFFFFFFFFFFFFFFULL;  // 64 bits set to 1
    
    // Signed integer types
    int8_t min_int8 = -0x80;  // Minimum value for 8-bit signed integer
    int8_t max_int8 = 0x7F;   // Maximum value for 8-bit signed integer
    
    int16_t min_int16 = -0x8000;  // Minimum value for 16-bit signed integer
    int16_t max_int16 = 0x7FFF;   // Maximum value for 16-bit signed integer
    
    int64_t min_int64 = -0x8000000000000000LL;  // Minimum value for 64-bit signed integer
    int64_t max_int64 = 0x7FFFFFFFFFFFFFFFLL;   // Maximum value for 64-bit signed integer
    
    // Printing values in binary and hexadecimal
    
    
    std::cout << "min_uint8: " << +min_uint8 << std::endl;
    std::cout << "max_uint8: " << +max_uint8 << std::dec << std::endl;
    
    std::cout << "min_uint16: " << +min_uint16  << std::endl;
    std::cout << "max_uint16: " << +max_uint16 << std::endl;
    
    std::cout << "min_uint64: " << +min_uint64 << std::endl;
    std::cout << "max_uint64: " << +max_uint64  << std::endl;
    
    std::cout << "min_int8: "  << +min_int8 << std::endl;
    std::cout << "max_int8: " << +max_int8 << std::endl;
    
    std::cout << "min_int16: " << +min_int16  << std::endl;
    std::cout << "max_int16: " << +max_int16  << std::endl;
    
    std::cout << "min_int64: " << +min_int64  << std::endl;
    std::cout << "max_int64: " << +max_int64  << std::endl;
    
    
    // Printing the new values
    std::cout << "max_uint8 after adding 1: " << +max_uint8+1 << std::endl;
    std::cout << "max_uint16 after adding 1: " << +max_uint16+1 << std::endl;
    std::cout << "max_uint64 after adding 1: " << +max_uint64 +1<< std::endl;
    
    
    // Printing the new values
    std::cout << "min_int8 after subtracting 1: " << +min_int8 -1 << std::endl;
    std::cout << "min_int16 after subtracting 1: " << +min_int16 -1 << std::endl;
    std::cout << "min_int64 after subtracting 1: " << +min_int64 -1 << std::endl;
    
    
    /// FLOATING POINT
    double result = 0.1 + 0.2;
    std::cout << result << "\n";
    //    assert(result ==0.3);
    std::cout << std::setprecision(18)<<result << "\n"; //print numbers to 18 digits of accuracy
    
    
    float result1 = 0.1f + 0.2f;
    std::cout << "Result: " << std::setprecision(18)<< result1 << std::endl;
    assert(result1 == 0.3f);
    
    
    double a = 0.1 + 0.2;
    double b = 0.3;
    double tolerance = 1e-9; // A small tolerance value
    
    bool areEqual = approxEquals(a, b, tolerance);
    
    if (areEqual) {
        std::cout << "a is approximately equal to b." << std::endl;
    } else {
        std::cout << "a is not equal to b." << std::endl;
    }
    
    
    std::vector<int> TotalcountofValues = countASCIOUTofFile();
    
    int countASCIvalues = TotalcountofValues[0];
    int countUniCodeChars = TotalcountofValues[1];
    std::string stringOfASCI = std::to_string(countASCIvalues);
    std::string stringOfUnicode = std::to_string(countUniCodeChars);
    std::cout<< "The number of ASCII values was: " << stringOfASCI << "\n";
    std::cout << "The number of Unicode values was:" << stringOfUnicode << "\n";
    
    return 0;
}
