//
//  functions.hpp
//  NumberConverter
//
//  Created by Tailang  Cao on 9/5/23.
//

#ifndef functions_hpp
#define functions_hpp
#include <istream>
#include <stdio.h>

int StringToInt(std::string numStr, int base);

int ConvertDec (std::string deciStr);

int ConvertBi (std::string biStr);

int ConvertHex (std::string hexStr);

std::string intToDecimalString(int deciInt);

std::string intToHexadecimalString(int deciInt);

std::string intToBinaryString(int deciInt);

#endif /* functions_hpp */
