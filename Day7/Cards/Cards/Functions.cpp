//
//  Functions.cpp
//  Cards
//
//  Created by Tailang  Cao on 8/29/23.
//

#include "Functions.hpp"
#include<iostream>
#include<cstdlib>
#include<string>
#include <algorithm>

std::vector<card> Deck(){
    std::vector suit_type = {"H", "S", "C", "D"};
    std::vector rank = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    
    card temp_card;
    std::vector<card> deck;
    
    for(std::string i : suit_type){
        for(std::string j : rank){
            temp_card.suit = i;
            temp_card.rank = j;
            deck.push_back(temp_card);
        }
        //        temp_card.suit = " ";
        //        temp_card.rank = " \n";
        //        deck.pop_back(temp_card);
    }
    return deck;
}

void printCards(std::vector<card>& Deck){
    for(card c : Deck){
        std::cout << c.suit << c.rank << " ";
    }
}

void swap(card& a, card& b){
    card temp = a;
    a = b;
    b = temp;
}

void Shuffle(std::vector<card>& Deck){
//    int ran_pos,ran_pos2;
    for(int i = 51; i > 0; i--){
        //        std::cout<<i;
//        ran_pos = rand()% (i+1);
//        ran_pos2 = i;
        swap(Deck[i], Deck[rand()%(i+1)]);
    }
}

std::vector<card> get_subdeck(std::vector<card> Deck){
    std::vector<card> subdeck;
    for (int i = 0; i<=4; i++){
        subdeck.push_back(Deck[i]);
    }
    return subdeck;
}

bool isFlush(std::vector<card> subdeck){
    for(int i = 0; i<4; i++){
        if (subdeck[i].suit != subdeck[i+1].suit){
            return false;
        }
    }
    return true;
}

bool A_Straight(std::vector<card> subdeck){
    std::vector<int> kill_me;

    for(card a:subdeck){
        if(a.rank=="A"){
            kill_me.push_back(1);
        }else if (a.rank=="J"){
            kill_me.push_back(11);
        }else if (a.rank=="Q"){
            kill_me.push_back(12);
        }else if (a.rank=="K"){
            kill_me.push_back(13);
        }else{
            kill_me.push_back(stoi(a.rank));
        }
    }
    sort(kill_me.begin(),kill_me.end());
    for (int i = 0; i < 4; i++ ){
        if(kill_me[i]!=(kill_me[i+1]-1)){
            return false;
        }
    }
    return true;
}

bool Norm_Straight(std::vector<card> subdeck){
    std::vector<int> kill_me;

    for(card a:subdeck){
        if(a.rank=="A"){
            kill_me.push_back(14);
        }else if (a.rank=="J"){
            kill_me.push_back(11);
        }else if (a.rank=="Q"){
            kill_me.push_back(12);
        }else if (a.rank=="K"){
            kill_me.push_back(13);
        }else{
            kill_me.push_back(stoi(a.rank));
        }
    }
    sort(kill_me.begin(),kill_me.end());
    for (int i = 0; i < 4; i++ ){
        if(kill_me[i]!=(kill_me[i+1]-1)){
            return false;
        }
    }
    return true;
}
    

bool isStraight(std::vector<card> subdeck){
    if(A_Straight(subdeck)||Norm_Straight(subdeck)){
        return true;
    }
    return false;
}

bool isStraightFlush(std::vector<card> subdeck){
    if(isFlush(subdeck)&&isStraight(subdeck)){
        return true;
    }
    return false;
}

bool isRoyalFlush(std::vector<card> subdeck){
    if(isStraightFlush(subdeck)){
        for(int i = 0; i < 4; i++ ){
            if(subdeck[i].rank == "A"){
                for(int j = 0; j<4; j++){
                    if(subdeck[j].rank == "K"){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


bool A_isFullHouse(std::vector<card> subdeck){
    std::vector<int> kill_me;

    for(card a:subdeck){
        if(a.rank=="A"){
            kill_me.push_back(1);
        }else if (a.rank=="J"){
            kill_me.push_back(11);
        }else if (a.rank=="Q"){
            kill_me.push_back(12);
        }else if (a.rank=="K"){
            kill_me.push_back(13);
        }else{
            kill_me.push_back(stoi(a.rank));
        }
    }
    sort(kill_me.begin(),kill_me.end());

    if(kill_me[0] != kill_me[1]){
        return false;
    }
    else if(kill_me[3] != kill_me[4]){
        return false;
    }
    if(kill_me[1]!=kill_me[2] && kill_me[2]!=kill_me[3]){
        return false;
    }
    else{
        return true;
    }
}


bool Norm_isFullHouse(std::vector<card> subdeck){
    std::vector<int> kill_me;

    for(card a:subdeck){
        if(a.rank=="A"){
            kill_me.push_back(14);
        }else if (a.rank=="J"){
            kill_me.push_back(11);
        }else if (a.rank=="Q"){
            kill_me.push_back(12);
        }else if (a.rank=="K"){
            kill_me.push_back(13);
        }else{
            kill_me.push_back(stoi(a.rank));
        }
    }
    sort(kill_me.begin(),kill_me.end());

    if(kill_me[0] != kill_me[1]){
        return false;
    }
                                if(kill_me[3] != kill_me[4]){
        return false;
    }
    if(kill_me[1]!=kill_me[2] && kill_me[2]!=kill_me[3]){
        return false;
    }
    else{
        return true;
    }
}


bool isFullhouse(std::vector<card> subdeck){
    if(A_isFullHouse(subdeck)||Norm_isFullHouse(subdeck)){
        return true;
    }
    return false;
}
