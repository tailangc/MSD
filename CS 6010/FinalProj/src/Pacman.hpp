//
//  Pacman.hpp
//  testSFML
//
//  Created by Tailang  Cao on 9/19/23.
//

#ifndef Pacman_hpp
#define Pacman_hpp

#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "Global.hpp"


class Pacman{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    int pacmanSpeed;
    Position position;
    int direction;
    
public:
    
    Pacman();
    void draw(sf::RenderWindow& myWindow);
    void setPosition(int x, int y);
    void update(std::array<std::array<Cell, 20>,21>& outputMap, Pacman& pacman);
    int eatPellet(std::array<std::array<Cell, 20>,21>& outputMap, Pacman& pacman);
    void initialPos(std::vector<std::string> map_script, Pacman& pacman);
    Position getPosition();
    int getPacmanSpeed(){
        return pacmanSpeed;
    }
};

#endif /* Pacman_hpp */
