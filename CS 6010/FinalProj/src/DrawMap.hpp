//
//  DrawMap.hpp
//  testSFML
//
//  Created by Tailang  Cao on 9/19/23.
//

#ifndef DrawMap_hpp
#define DrawMap_hpp
#include <string>
#include <iostream>
#include "Global.hpp"
#include <stdio.h>

void drawMap (std::array<std::array<Cell, 20>,21> outputMap, sf::RenderWindow& window);

#endif /* DrawMap_hpp */
