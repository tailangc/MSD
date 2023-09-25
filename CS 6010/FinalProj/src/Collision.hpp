//
//  Collision.hpp
//  testSFML
//
//  Created by Tailang  Cao on 9/20/23.
//

#ifndef Collision_hpp
#define Collision_hpp
#include <array>
#include "Global.hpp"
#include <stdio.h>

bool collision (bool collectPellet, bool useDoor, int x, int y, std::array<std::array<Cell, 20>,21>& outputMap);

#endif /* Collision_hpp */


