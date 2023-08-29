//
//  main.cpp
//  RomanNumerals
//
//  Created by Tailang  Cao on 8/24/23.
//

#include <iostream>

int main() {
    int num;
    
    std::cout << "Enter decimal number: \n";
    std::cin >> num;
    
    if(num < 0){
        std::cout << "Invalid input. \n";
        return 0;
    }
    
    
    std::cout << "Roman numeral version: \n";
    
    
    while(num > 0){
        if(num >= 1000){
            std::cout << "M";
            num = num - 1000;
        }
        else if(num >= 900){
            std::cout << "CM";
            num = num - 900;
        }
        else if(num >= 500){
            std::cout << "D";
            num = num - 500;
        }
        else if(num >= 400){
            std::cout << "CD";
            num = num - 400;
        }
        else if(num >= 100){
            std::cout << "C";
            num = num - 100;
        }
        else if (num >= 90){
            std::cout << "XC";
            num = num - 90;
        }
        else if (num >= 50){
            std::cout << "L";
            num = num - 50;
        }
        else if (num >= 40){
            std::cout << "XL";
            num = num - 40;
        }
        else if(num >= 10){
            std::cout << "X";
            num = num - 10;
        }
        else if(num >= 9){
            std::cout << "IX";
            num = num - 9;
        }
        else if(num >= 5){
            std::cout << "V";
            num = num - 5;
        }
        else if(num >= 4){
            std::cout << "IV";
            num = num -4;
        }
        else if(num >= 1){
            std::cout << "I";
            num = num -1;
        }
    }
  
    std::cout << "\n";
    
    return 0;
}
