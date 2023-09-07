//
//  main.cpp
//  NumberConverter
//
//  Created by Tailang  Cao on 9/5/23.
//

#include <iostream>
#include "functions.hpp"

int main(int argc, const char * argv[]) {
//    std::string deciStr = "-ff";
//    int base = 16;
//    int deciNum = StringToInt(deciStr, base);
//    std::cout << deciNum;
    
//    int deciInt = -456;
//
//    std::cout << intToBinaryString(deciInt);
    std::cout << StringToInt(intToHexadecimalString(-10), 16);
    
    
    return 0;
}
