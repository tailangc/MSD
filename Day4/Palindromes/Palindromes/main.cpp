//
//  main.cpp
//  Palindromes
//
//  Created by Tailang  Cao on 8/24/23.
//

#include <iostream>

int main() {
    std::string original, reverse;
    std::cout << "Please enter a word: \n";
    std::cin >> original;

    int character = original.length();
    for (int i = character-1; i >= 0; i -= 1){
        reverse += original[i];
    }

    if(original == reverse){
        std::cout << original << " IS a palindrome \n";
    }

    else{
        std::cout << original << " is NOT a palindrome \n";
    }

    return 0;
}





