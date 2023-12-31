//
//  main.cpp
//  Cards
//
//  Created by Tailang  Cao on 8/29/23.
//

#include <iostream>
#include"Functions.hpp"

int main() {
    
    std::vector<Card> deck = Deck();
    
    
    
    std::vector<Card> subdeck = get_subdeck(deck);
    
    int i = 0;
    int numFlush = 0, numStraight = 0, numStraightFlush = 0, numRoyalFlush = 0, numFullHouse = 0;
    double testNum = 1000000;
    while(i <= testNum){
        if(isFlush(subdeck)){
            numFlush += 1;
        }
        if(isStraight(subdeck)){
            numStraight += 1;
        }
        if(isStraightFlush(subdeck)){
            numStraightFlush += 1;
        }
        if(isRoyalFlush(subdeck)){
            numRoyalFlush += 1;
        }
        if(isFullhouse(subdeck)){
            numFullHouse += 1;
        }
        
        Shuffle(deck);
        subdeck = get_subdeck(deck);
    
        i += 1;
    }
    
    double flushPos, straightPos, straightFlushPos, royalFlushPos, fullHousePos;
    flushPos = (numFlush*100) / testNum;
    straightPos = (numStraight*100) / testNum;
    straightFlushPos = (numStraightFlush*100) / testNum;
    royalFlushPos = (numRoyalFlush*100) / testNum;
    fullHousePos = (numFullHouse*100) / testNum;
    std::cout << "Possibility of flush is: " << flushPos << "%" << "\n";
    std::cout << "Possibility of straight is: " << straightPos << "%" << "\n";
    std::cout << "Possibility of straight flush: " << straightFlushPos << "%" << "\n";
    std::cout << "Possibility of royal flush is: " << royalFlushPos << "%" << "\n";
    std::cout << "Possibility of fullhouse is: " << fullHousePos << "%" << "\n";
        
    

    
//    for(card c : deck){
//        std::cout << c.suit << c.rank << " ";
//    }
    

    
//    std::vector<card> deck = {{"S","A"},{"S","K"},{"S","10"},{"S","Q"},{"S","J"}};
//    if(isStraightFlush(deck)){
//        std::cout << "It's straight flush ";
//    }
//    if(isRoyalFlush(deck)){
//        for(card c : deck){
//            std::cout << "its royalflush ";
//        }
//    }
    
//    for(card c : deck){
//        std::cout << c.suit << c.rank << " ";
//    }
    
    return 0;
}
