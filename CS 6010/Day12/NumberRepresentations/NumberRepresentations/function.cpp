//
//  function.cpp
//  NumberRepresentations
//
//  Created by Tailang  Cao on 9/7/23.
//

#include "function.hpp"
#include <cmath>
#include <fstream>

// comparing the value with its tolerance with the value its supposed to be i.e., .1 + .2 value and .3 utilizing the tolerance
bool approxEquals( double a, double b, double tolerance ){
    return std::abs(a - b) <= tolerance;
}

 std::vector <int> countASCIOUTofFile(){
 std::vector<int>numberOfBoth;
  char charOfbook;
  std::ifstream book;
  int countASCIvalues = 0;
  int decimalNumber = 0;
  std::string asciOrUt;
  int countUniCodeChars = 0;
  book.open ("Unicode.txt");
  // stream the book data into characters -> charOfBook
  while( book >> charOfbook ){
    // print character from book
    std::cout << charOfbook;
    // make the char into int with + and convert it to a string (base 10)
    asciOrUt = std::to_string(+charOfbook);
    // print string value from the integer from the character
    std::cout<< ' ' << asciOrUt << "\n";
    //conver the string to an integer
    decimalNumber = std::stoi(asciOrUt);
    if(decimalNumber >= 0 and decimalNumber < 128){
      countASCIvalues += 1;
    }
    countUniCodeChars += 1;
  }
   numberOfBoth.push_back(countASCIvalues);
   numberOfBoth.push_back(countUniCodeChars);
  return numberOfBoth;
}
