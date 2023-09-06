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

struct Card{std::string suit; std::string rank;};

void printCards(std::vector<Card>& Deck);

std::vector<Card> Deck();

void swap(int& a, int& b);

void Shuffle(std::vector<Card>& Deck);

std::vector<Card> get_subdeck(std::vector<Card> Deck);

bool isFlush(std::vector<Card> subdeck);

bool isStraight(std::vector<Card> subdeck);

bool isStraightFlush(std::vector<Card> subdeck);

bool A_Straight(std::vector<Card> subdeck);

bool Norm_Straight(std::vector<Card> subdeck);

bool isRoyalFlush(std::vector<Card> subdeck);

bool A_isFullHouse(std::vector<Card> subdeck);

bool Norm_isFullHouse(std::vector<Card> subdeck);

bool isFullhouse(std::vector<Card> subdeck);


#endif /* Functions_hpp */
