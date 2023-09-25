//
//  main.cpp
//  StringAnalyzer
//
//  Created by Tailang  Cao on 8/25/23.
//

#include <iostream>
#include "LetterHelpers.hpp"
#include "WordHelpers.hpp"


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
        average_vowel_per_word = AverageVowelPerWord(input);
        std::cout << " Average ovowels per word: " << average_vowel_per_word << "\n\n";
        
        std::cout << "Enter a string containing one or more sentences,type in 'done' for finish: \n";
        std::getline( std::cin, input);
        
    }
    std::cout << "Goodbye \n";
    
    
    
    
    
    return 0;
}
