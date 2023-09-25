//
//  main.cpp
//  NumberConverter
//
//  Created by Tailang  Cao on 9/5/23.
//

#include <iostream>
#include "functions.hpp"

int main(int argc, const char * argv[]) {
    
    int value = StringToInt ("99" , 10 );
    std::cout << "stringToInt( \"99\" , 10 ) = " << value <<std::endl;
    
    int value2 = StringToInt( "1100", 2 );
    std::cout<< "stringToInt( \"1100\", 2 ) = "<< value2 <<std::endl;
    int value3 = StringToInt( "FF", 16 );
    std::cout<< "stringToInt( \"FF\", 16 ) = " << value3 <<std::endl;
    std::string decimals = intToDecimalString( 10 );
    std::cout<< "intToDecimalString( 10 ) = " <<decimals<<std::endl;
    
    std::string Hexadecimals= intToHexadecimalString(-10);
    std::cout<< "intToBinaryString( -10 ) = "<<Hexadecimals<<std::endl;
    std::string biStr = intToBinaryString (10);
    std::cout << "intToHexadecimalString( 10 ) = "<<biStr<<std::endl;
    
    std::cout << StringToInt(intToHexadecimalString( -5 ), 16 )<<std::endl;
    return 0;
    
}
