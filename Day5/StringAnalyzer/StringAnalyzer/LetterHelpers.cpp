//
//  LetterHelpers1.cpp
//  StringAnalyzer
//
//  Created by Tailang  Cao on 8/28/23.
//

#include "LetterHelpers.hpp"


bool IsTerminator(char c){
    if(c == '.' || c == '!' || c == '?'){
        return true;
    }
    return false;
}


bool IsPunctuation(char c){
    if(c == '.' || c == '!' || c == '?' || c == ','){
        return true;
    }
    return false;
}


bool IsVowel(char c){
    if (c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'y' || c == 'Y'){
        return true;
    }
    return false;
}

bool IsConsonants(char c){
    if (c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == ' ' || c == '!' || c == '?' || c == '.' || c == ',' || c == 'y' || c == 'Y'){
        return false;
    }
    return true;
}
