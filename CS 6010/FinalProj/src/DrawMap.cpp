//
//  DrawMap.cpp
//  testSFML
//
//  Created by Tailang  Cao on 9/19/23.
//
#include <SFML/Graphics.hpp>
#include "DrawMap.hpp"
#include "Global.hpp"
Global global = Global();

sf::RectangleShape rectangle;
sf::CircleShape pellet(3.f);
sf::RectangleShape door;

void drawMap (std::array<std::array<Cell, 20>,21> outputMap, sf::RenderWindow& window){
    
    for(int a = 0; a < 20 ; a++){
        for(int b = 0; b < 21; b++){
            switch (outputMap[a][b]) {
                case Cell::Wall:
                {
                    rectangle.setPosition(a* global.getCellSize(), b*global.getCellSize());
                    rectangle.setSize(sf::Vector2f(global.getCellSize(), global.getCellSize()));
                    rectangle.setFillColor(sf::Color::Blue);
                    window.draw(rectangle);
                    break;
                }
                case Cell::Pellet:
                {
                    pellet.setPosition(a* global.getCellSize() + 10, b*global.getCellSize() + 10);
                    pellet.setFillColor(sf::Color::Yellow);
                    window.draw(pellet);
                    break;
                }
                case Cell::Door:
                {
                    door.setPosition(a* global.getCellSize(), b*global.getCellSize());
                    door.setSize(sf::Vector2f(global.getCellSize(), global.getCellSize()));
                    door.setFillColor(sf::Color(5,70,70));
                    window.draw(door);
                }
            }
                
            
            
                
            }
        }
    }

