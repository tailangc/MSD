//
//  WordHelpers.cpp
//  StringAnalyzer
//
//  Created by Tailang  Cao on 8/28/23.
//

#include "WordHelpers.hpp"
#include <string>

int NumWords(std::string s){
    int count = 0;
    int i = 0;
    char x;
    while(i < s.length()){ 
        x = s[i];
        if(x == ' '){
            count += 1;
        }
        i += 1;
    }
    count += 1;
    return count;
}


int NumSentences(std::string s){
    int count = 0;
    int i = 0;
    char x;
    while(i < s.length()){
        x = s[i];
        if(IsTerminator(x)){
            count += 1;
        }
        i += 1;
    }
    return count;
}


int NumVowels(std::string s){
    int i = 0;
    int count = 0;
    char x;
    while(i < s.length()){
        x = s[i];
        if (IsVowel(x)){
            count += 1;
        }
        i += 1;
    }
    return count;
}


int NumConsonants(std::string s){
    int i = 0;
    int count = 0;
    char x;
    while(i < s.length()){
        x = s[i];
        if (IsConsonants(x)){
            count += 1;
        }
        i += 1;
    }
    return count;
}


double AverageWordLength(std::string s){
    double count, num_vowels, num_consonants, num_words;
    num_vowels = NumVowels(s);
    num_consonants = NumConsonants(s);
    num_words = NumWords(s);
    count = (num_vowels + num_consonants) / num_words;
    return count;
}


double AverageVowelPerWord(std::string s){
    double count,num_vowels, num_words;
    num_vowels = NumVowels(s);
    num_words = NumWords(s);
    count = num_vowels / num_words;
    return count;
}
