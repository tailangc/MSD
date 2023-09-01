//
//  main.cpp
//  Cards
//
//  Created by Tailang  Cao on 8/29/23.
//

#include <iostream>
#include"Functions.hpp"

int main() {
    
//    std::vector<card> deck = Deck();
//    Shuffle(deck);
    
//    std::vector<card> subdeck = get_subdeck(deck);
    
//    for(card sub : subdeck){
//        std::cout << sub.suit << sub.rank << " ";
//    }
    std::vector<card> deck = {{"S","1"},{"S","2"},{"S","3"},{"S","5"},{"S","4"}};
//
    if(isStraight(deck)==false){
        std::cout << "false";
    }
    else{
        std::cout << "true";
    }
    
//    for(card c : deck){
//        std::cout << c.suit << c.rank << " ";
//    }
    return 0;
}
