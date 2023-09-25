//
//  Ghost.hpp
//  testSFML
//
//  Created by Tailang  Cao on 9/21/23.
//

#ifndef Ghost_hpp
#define Ghost_hpp
#include <iostream>
#include <array>
#include "Global.hpp"
#include "Collision.hpp"
#include <SFML/Graphics.hpp>
#include "Pacman.hpp"
#include <cmath>

#include <stdio.h>

class Ghost{
    int direction;
    Position position;
    Position target;
    int ghostSpeed;
    sf::Texture texture; 
    sf::Sprite sprite;
    
public:
    Ghost();
    
    void draw(sf::RenderWindow& myWindow);
    Position getPosition();
    void setPosition(int x, int y);
    void initialPos(std::vector<std::string> map_script, Ghost& ghost);
    void update(std::array<std::array<Cell, 20>, 21>& map, Ghost& ghost, Pacman& pacman);
    float getDistance (int direction, Pacman pacman);
};

#endif /* Ghost_hpp */
