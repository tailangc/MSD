//
//  functions.cpp
//  Book Analyzer
//
//  Created by Tailang  Cao on 9/1/23.
//

#include "functions.hpp"
#include <iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<iomanip>
#include<algorithm>

int getWordCount (std::vector<std::string> allWord, std::string filename){
    int wordCount = 0;
    std::ifstream myfile(filename);
    std::string word;
    
    if(myfile.is_open()){
        while(myfile >> word){
            wordCount += 1;
        }
    }
    return wordCount;
}
std::vector<std::string> getAllWord (std::string filename){
    
    std::vector<std::string> allword;
    
    std::ifstream myfile(filename);
    if(myfile.fail()){
        std::cout << "Failed to open file.\n";
        exit(1);
    }
    
    return allword;
}

int getTitlePos (std::vector<std::string> allWord){
    int titlePos = -1;
    for(int i = 0; i < 100 ; i++){
        if(allWord[i] == "Title:"){
            titlePos = i;
        }
    }
    return titlePos;
}

int getAuthorPos (std::vector<std::string> allWord, int titlePos){
    int authorPos = -1;
    for(int i = titlePos; i < titlePos + 100; i++){
        if(allWord[i] == "Author:"){
            authorPos = i;
        }
    }
    return authorPos;
}

int getDatePos (std::vector<std::string> allWord, int authorPos){
    int datePos = -1;
    for(int i = authorPos; i < authorPos + 100; i++){
        if(allWord[i] == "Release" && allWord[i+1] == "Date:"){
            datePos = i + 2;
        }
    }
    return datePos;
}

std::string getTitle (int titlePos, int authorPos, std::vector<std::string> allWord){
    std::string title = "";
    if(titlePos!= -1){
        for (int i = titlePos + 1; i < authorPos; i++){
            title = title  + allWord[i] + " ";
        }
    }
    else{
        title =  "Unknow Title";
    }
    return title;
}

std::string getAuthor (int authorPos, int datePos, std::vector<std::string> allWord){
    std::string author = "";
    if(authorPos!=-1){
        for(int i = authorPos + 1; i < datePos; i++){
            author = author + allWord[i] + " ";
        }
    }
    else{
        author = "Unknow Author";
    }
    return author;
}

int getCharCount (std::vector<std::string> allWord){
    int charCount = 0;
    for(int i = 0; i < allWord.size(); i++){
        charCount += allWord[i].size();
    }
    return charCount;
}

int getKeyCount (std::vector<std::string> allWord, std::string keyWord){
    int keyCount = 0;
    for(int i = 0; i < allWord.size(); i++){
        if (allWord[i] == keyWord){
            keyCount+=1;
        }
    }
    return keyCount;
}

std::vector<int> getAllKeyPos (std::vector<std::string> allWord, std::string keyWord, int charCount){
    int keyCharCount = 0;
    std::vector<int> allKeyPos;
    for(int i = 0; i < allWord.size(); i++){
        keyCharCount += allWord[i].size();
        if (allWord[i] == keyWord){
            double keyPos = (static_cast<double>(keyCharCount) / charCount) * 100;
            allKeyPos.push_back(keyPos);
        }
    }
    return allKeyPos;
}

std::vector<std::string> getAllKeySentence (std::vector<std::string> allWord, std::string keyWord){
    std::string keySentence;
    std::vector<std::string> allKeySentence;
    for(int i = 0; i < allWord.size(); i++){
        if (allWord[i] == keyWord){
            keySentence = allWord[i-1] + " " + allWord[i] + " " + allWord[i+1];
            allKeySentence.push_back(keySentence);
        }
    }
    return allKeySentence;
}

std::string getShortWord (std::vector<std::string> allWord){
    std::string shortWord = allWord[0];
    for(int i=0; i<allWord.size(); i++){
        if(allWord[i].size() < shortWord.size()){
            shortWord = allWord[i];
        }
    }
    return shortWord;
}

std::string getLongWord (std::vector<std::string> allWord){
    std::string longWord;
    longWord = allWord[0];
    for(int i=0; i<allWord.size(); i++){
        if(allWord[i].size() > longWord.size()){
            longWord = allWord[i];
        }
    }
    return longWord;
}



