//
//  Functions.cpp
//  Cards
//
//  Created by Tailang  Cao on 8/29/23.
//

#include "Functions.hpp"
#include<iostream>



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


