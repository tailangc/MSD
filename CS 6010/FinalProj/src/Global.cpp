//
//  Global.cpp
//  testSFML
//
//  Created by Tailang  Cao on 9/20/23.
//

#include "Global.hpp"

Global::Global(){
    cellSize = 30;
    mapWidth = 20;
    mapHeight = 21;
}

int Global::getCellSize(){
    return cellSize;
}

int Global::getMapWidth(){
    return mapWidth;
}

int Global::getMapHeight(){
    return mapHeight;
}
