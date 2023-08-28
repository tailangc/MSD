//
//  main.cpp
//  StringAnalyzer
//
//  Created by Tailang  Cao on 8/25/23.
//

#include <iostream>


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


int main() {
    
    std::cout << "Enter a string containing one or more sentences, type in 'done' for finish: \n";
    std::string input;
    std::getline( std::cin, input);

    int num_words = 0, num_sentences = 0, num_vowels = 0, num_consonants = 0;
    double average_word_length = 0, average_vowel_per_word = 0;
    

    while (input != "done"){
        std::cout << "Analysis: \n";
        num_words = NumWords(input);
        std::cout << " Number of words: " << num_words << "\n";
        num_sentences = NumSentences(input);
        std::cout << " Number of sentences: " <<  num_sentences << "\n";
        num_vowels = NumVowels(input);
        std::cout << " Number of vowels: " << num_vowels << "\n";
        num_consonants = NumConsonants(input);
        std::cout << " Number of consonants: " << num_consonants << "\n";
        average_word_length = AverageWordLength(input);
        std::cout << " Reading level (average word length): " << average_word_length << "\n";
        average_vowel_per_word += AverageVowelPerWord(input);
        std::cout << " Average ovowels per word: " << average_vowel_per_word << "\n\n";
        
        std::cout << "Enter a string containing one or more sentences, type in 'done' for finish: \n";
        std::getline( std::cin, input);
        
    }
    std::cout << "Bye Bitch \n";
    
    
    
    
    
    return 0;
}
