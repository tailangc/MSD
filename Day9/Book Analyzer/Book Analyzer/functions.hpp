//
//  functions.hpp
//  Book Analyzer
//
//  Created by Tailang  Cao on 9/1/23.
//

#ifndef functions_hpp
#define functions_hpp
#include <iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<iomanip>
#include<algorithm>
#include <stdio.h>

std::vector<std::string> getAllWord (std::string filename);
int getWordCount (std::vector<std::string> allWord, std::string filename);
int getTitlePos (std::vector<std::string> allWord);
int getAuthorPos (std::vector<std::string> allWord, int titlePos);
int getDatePos (std::vector<std::string> allWord, int authorPos);
std::string getTitle (int titlePos, int authorPos, std::vector<std::string> allWord);
std::string getAuthor (int authorPos, int datePos, std::vector<std::string> allWord);
int getCharCount (std::vector<std::string> allWord);
int getKeyCount (std::vector<std::string> allWord, std::string keyWord);
std::vector<int> getAllKeyPos (std::vector<std::string> allWord, std::string keyWord, int charCount);
std::vector<std::string> getAllKeySentence (std::vector<std::string> allWord, std::string keyWord);
std::string getShortWord (std::vector<std::string> allWord);
std::string getLongWord (std::vector<std::string> allWord);

#endif /* functions_hpp */
