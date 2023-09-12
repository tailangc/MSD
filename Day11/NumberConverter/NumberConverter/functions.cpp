//
//  functions.cpp
//  NumberConverter
//
//  Created by Tailang  Cao on 9/5/23.
//

#include "functions.hpp"
#include <istream>
#include <iostream>


int StringToInt(std::string numStr, int base){
    int numericValue;
    if (base == 10){
        numericValue = ConvertDec(numStr);
    }
    else if (base == 2){
        numericValue = ConvertBi(numStr);
    }
    else if (base == 16){
        numericValue = ConvertHex(numStr);
    }
    else{
        return 0;
    }
    
    if (numStr[0] == '-'){
        numericValue = -1 * numericValue;
    }
    return numericValue;
}


int ConvertDec (std::string deciStr){
    int decNum = 0;
    int numericValue;
    if(deciStr[0] == '-'){
        deciStr = deciStr.substr(1, deciStr.size()-1);
        }
    for (int i = 0; i < deciStr.size(); i++){
        numericValue = (deciStr[i] - '0') * pow(10, (deciStr.size()-i-1));
        decNum += numericValue;
    }
    return decNum;
}



int ConvertBi (std::string biStr){
    int decNum = 0;
    int numericValue;
    if(biStr[0] == '-'){
        biStr = biStr.substr(1, biStr.size()-1);
        }
    for (int i = 0; i < biStr.size(); i++){
        numericValue = (biStr[i] - '0') * pow(2, (biStr.size()-i-1));
        decNum += numericValue;
    }
    return decNum;
}



int ConvertHex (std::string hexStr){
    int decNum = 0;
    int numericValue;
    if(hexStr[0] == '-'){
        hexStr = hexStr.substr(1, hexStr.size()-1);
        }
    for (int i = 0; i < hexStr.size(); i++){
        if (hexStr[i] > 47 && hexStr[i] < 58){
            numericValue = (hexStr[i] - '0') * pow(16, (hexStr.size()-i-1));
        }
        else{
            numericValue = (tolower(hexStr[i]) - 'a' + 10) * pow(16, (hexStr.size()-i-1));
        }
        decNum += numericValue;
    }
    return decNum;
}


// 45/8(3)=5
std::string intToDecimalString(int deciInt){
    std::string deciString = std::to_string(deciInt);
    return deciString;
}



std::string intToHexadecimalString(int deciInt){
    int i = 0;
    int highExpo = 0;
    int temp;
    int posIndicator = 1;
    std::string hexaStr;
    if(deciInt < 0){
        deciInt = (-1) * deciInt;
        posIndicator = -1;
    }
    
    while(i >= 0){;
        if(deciInt / pow(16,i) < 16){
            highExpo = i;
            break;
        }
        i++;
    }
    for(int i = highExpo; i >= 0; i--){
        temp = deciInt / pow(16, i);
        deciInt -= temp * pow(16, i);
        if(temp == 10){
            hexaStr += "A";
        }
        else if(temp == 11){
            hexaStr += "B";
        }
        else if(temp == 12){
            hexaStr += "C";
        }
        else if(temp == 13){
            hexaStr += "D";
        }
        else if(temp == 14){
            hexaStr += "E";
        }
        else if(temp == 15){
            hexaStr += "F";
        }
        else{
            hexaStr += std::to_string(temp);
        }
    }
    if (posIndicator == -1){
        hexaStr = "-" + hexaStr;
    }
    return hexaStr;
}



std::string intToBinaryString(int deciInt){
    int i = 0;
    int highExpo = 0;
    int temp;
    int posIndicator = 1;
    std::string biStr;
    if(deciInt < 0){
        deciInt = (-1) * deciInt;
        posIndicator = -1;
    }
    while(i >= 0){;
        if(deciInt / pow(2,i) < 2){
            highExpo = i;
            break;
        }
        i++;
    }
    for(int i = highExpo; i >= 0; i--){
        temp = deciInt / pow(2, i);
        deciInt -= temp * pow(2, i);
        biStr += std::to_string(temp);
    }
    if (posIndicator == -1){
        biStr = "-" + biStr;
    }
    return biStr;
}

