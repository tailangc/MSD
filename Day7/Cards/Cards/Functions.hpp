//
//  Functions.hpp
//  Cards
//
//  Created by Tailang  Cao on 8/29/23.
//

#ifndef Functions_hpp
#define Functions_hpp
#include <iostream>
#include <stdio.h>
#include<cstdlib>
#include<string>

struct card{std::string suit; std::string rank;};

void printCards(std::vector<card>& Deck);

std::vector<card> Deck();

void swap(int& a, int& b);

void Shuffle(std::vector<card>& Deck);

std::vector<card> get_subdeck(std::vector<card> Deck);

bool isFlush(std::vector<card> subdeck);

bool isStraight(std::vector<card> subdeck);

bool isStraightFlush(std::vector<card> subdeck);

bool A_Straight(std::vector<card> subdeck);

bool Norm_Straight(std::vector<card> subdeck);

bool isRoyalFlush(std::vector<card> subdeck);

bool A_isFullHouse(std::vector<card> subdeck);

bool Norm_isFullHouse(std::vector<card> subdeck);

bool isFullhouse(std::vector<card> subdeck);


#endif /* Functions_hpp */
