//
//  WordHelpers.hpp
//  StringAnalyzer
//
//  Created by Tailang  Cao on 8/28/23.
//

#ifndef WordHelpers_hpp
#define WordHelpers_hpp

#include "LetterHelpers.hpp"
#include <stdio.h>
#include <string>
#endif /* WordHelpers_hpp */

int NumWords(std::string s);

int NumSentences(std::string s);

int NumVowels(std::string s);

int NumConsonants(std::string s);

double AverageWordLength(std::string s);

double AverageVowelPerWord(std::string s);
