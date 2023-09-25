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

std::vector<Card> Deck(){
    std::vector<std::string> suit_type = {"H", "S", "C", "D"};
    std::vector rank = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    
    Card temp_card;
    std::vector<Card> deck;
    
    for(const std::string &i : suit_type){
        for(const std::string& j : rank){
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

void printCards(const std::vector<Card>& Deck){
    for(const Card& c : Deck){
        std::cout << c.suit << c.rank << " ";
    }
}

void swap(Card& a, Card& b){
    Card temp = a;
    a = b;
    b = temp;
}

void Shuffle(std::vector<Card>& Deck){
//    int ran_pos,ran_pos2;
    for(int i = 51; i > 0; i--){
        //        std::cout<<i;
//        ran_pos = rand()% (i+1);
//        ran_pos2 = i;
        swap(Deck[i], Deck[rand()%(i+1)]);
    }
}

// Get subdeck by pushing back the first five elements into a new vector;
std::vector<Card> get_subdeck(std::vector<Card> Deck){
    std::vector<Card> subdeck;
    for (int i = 0; i<=4; i++){
        subdeck.push_back(Deck[i]);
    }
    return subdeck;
}

//Check if the handcard is a flush by checking if all the former suit equals to the next suit
bool isFlush(std::vector<Card> subdeck){
    for(int i = 0; i<4; i++){
        if (subdeck[i].suit != subdeck[i+1].suit){
            return false;
        }
    }
    return true;
}


//Check if the handcard is straight
//Transforming face card and A into numbers to create a vector that is sortable. (A in the condition of 1)
//Check if all the former card rank in the handcard after sorting is one number smaller than the card rank after it
bool A_Straight(std::vector<Card>& subdeck){
    std::vector<int> kill_me;

    for(Card a:subdeck){
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

//Check if the handcard is straight
//Transforming face card and A into numbers to create a vector that is sortable. (A in the condition of 14)
//Check if all the former card rank in the handcard after sorting is one number smaller than the card rank after it
bool Norm_Straight(std::vector<Card> subdeck){
    std::vector<int> kill_me;

    for(Card a:subdeck){
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
    

bool isStraight(std::vector<Card> subdeck){
    if(A_Straight(subdeck)||Norm_Straight(subdeck)){
        return true;
    }
    return false;
}


bool isStraightFlush(std::vector<Card> subdeck){
    if(isFlush(subdeck)&&isStraight(subdeck)){
        return true;
    }
    return false;
}


// Check if the handcard is royal flush under the circumstance of a straight flush.
// See through the hand card to see if there exist rank 'A'.
// See through the hand card to see if there exist rank 'K'.
// If the two both exist and its a straight flush, then its a royal flush.
bool isRoyalFlush(std::vector<Card> subdeck){
    if(isStraightFlush(subdeck)){
        for(int i = 0; i < 4; i++ ){
            if(subdeck[i].rank == "A"){
                for(int j = 0; j<4; j++){
                    if(subdeck[j].rank == "K"){
                        return true;//change to singlr for loop with sorting function
                    }
                }
            }
        }
    }
    return false;
}


bool A_isFullHouse(std::vector<Card> subdeck){
    std::vector<int> kill_me;

    for(Card a:subdeck){
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


bool Norm_isFullHouse(std::vector<Card> subdeck){
    std::vector<int> kill_me;

    for(Card a:subdeck){
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


bool isFullhouse(std::vector<Card> subdeck){
    if(A_isFullHouse(subdeck)||Norm_isFullHouse(subdeck)){
        return true;
    }
    return false;
}
