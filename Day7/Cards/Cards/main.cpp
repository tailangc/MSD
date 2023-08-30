//
//  main.cpp
//  Cards
//
//  Created by Tailang  Cao on 8/29/23.
//

#include <iostream>
#include"Functions.hpp"

int main() {
    
    for(card c : Deck()){
        std::cout << c.suit << c.rank << " ";
    }
    
    return 0;
}
