//
//  main.cpp
//  Book Analyzer
//
//  Created by Tailang  Cao on 9/1/23.
//

#include <iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<iomanip>
#include<algorithm>


int main(int argc, const char * argv[]) {
    
    
    std::string filename = argv[1];
    std::string keyword = argv[2];
    
    std::ifstream myfile(filename);
    
    if(myfile.fail()){
        std::cout << "Failed to open file.\n";
        exit(1);
    }
    
    std::string word;
    std::vector<std::string> allword;
    int wordCount = 0;
//    int titleStart;
    
    if(myfile.is_open()){
        while(myfile >> word){
            allword.push_back(word);
            wordCount += 1;
        }
//        std::cout << "The current data is: " << data << "\n";
    }
    
    int titlePos = -1;
    int authorPos = -1;
    int datePos = -1;
    
    for(int i = 0; i < allword.size(); i++){
        if(allword[i] == "Title:"){
            titlePos = i;
        }
        if(allword[i] == "Author:"){
            authorPos = i;
        }
        if(allword[i] == "Release" && allword[i+1] == "Date:"){
            datePos = i + 2;
        }
    }
    
    std::string title, author;
    if(titlePos!= -1){
        for (int i = titlePos + 1; i < authorPos; i++){
            title += allword[i] + " ";
        }
    }
    else{
        title =  "Unknow Title";
    }
        
    if(authorPos!=-1){
        for(int i = authorPos + 1; i < datePos; i++){
            author += allword[i] + " ";
        }
    }
    else{
        author = "Unknow Author";
    }
    
//    if(datePos!= -1 && datePos < allword.size()){
//        std::cout << allword[datePos] << " " << allword[datePos + 1] << " " << allword[datePos + 2] << "\n";
//    }
//    else{
//        std::cout << "Unknow Release Date\n";
//    }
    
    
    
    int charCount=0;
    int keyCharCount = 0;
    int keyCount=0;
    
    std::string keySentence;
    std::vector<std::string> allKeySentence;
    std::vector<int> allKeyPos;

    
    for(int i = 0; i < allword.size(); i++){
        charCount += allword[i].size();
    }
    
    for(int i = 0; i < allword.size(); i++){
        keyCharCount += allword[i].size();
        if (allword[i]==keyword){
            double keyPos = (static_cast<double>(keyCharCount) / charCount) * 100;
            allKeyPos.push_back(keyPos);
            keyCount+=1;
            keySentence = allword[i-1] + " " + allword[i] + " " + allword[i+1];
            allKeySentence.push_back(keySentence);
            
        }
    }
    
    
    
    
    std::string shortWord;
    std::string longWord;
    
    shortWord = allword[0];
    for(int i=0; i<allword.size(); i++){
        if(allword[i].size() < shortWord.size()){
            shortWord = allword[i];
        }
    }
    
    longWord = allword[0];
    for(int i=0; i<allword.size(); i++){
        if(allword[i].size() > longWord.size()){
            longWord = allword[i];
        }
    }
    
    

    
    
    std::cout << "\nStatistics for " << title << "by " << author << ":\n";
    std::cout << "Number of words: " << wordCount << "\n";
    std::cout << "Number of characters: " << charCount << "\n";
    std::cout << "The shortest word is \"" << shortWord << "\", and the longest word is \"" << longWord << "\"\n\n";
    std::cout << "The word \"" << keyword << "\" appears " << keyCount << " times: \n";
    
    for(int i = 0; i < keyCount; i++){
        std::cout << "at " << allKeyPos[i] << "%: " << allKeySentence[i] << "\n";
    }
    
    
    
    return 0;
}




