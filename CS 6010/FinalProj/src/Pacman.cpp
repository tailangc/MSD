//
//  Pacman.cpp
//  testSFML
//
//  Created by Tailang  Cao on 9/19/23.
//

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Global.hpp"
#include "Pacman.hpp"
#include "Collision.hpp"
//Global global = Global();

Pacman::Pacman(){
    position.x = 0;
    position.y = 0;
    pacmanSpeed = 5;
    direction = 0;
}

Position Pacman::getPosition(){
    return position;
}

void Pacman::setPosition(int x, int y){
//    position = Position{x,y};
    position.x = x;
    position.y = y;
}

void Pacman::draw(sf::RenderWindow& myWindow){
    if(!texture.loadFromFile("/Users/tailangcao/myGithubRepo/FinalProj/src/pacman.png")) {
    // 处理加载失败的情况
    // 可以选择使用默认图像或输出错误消息
}
    sprite.setPosition(position.x, position.y);
    sprite.setTexture(texture);
    myWindow.draw(sprite);
}

void Pacman::update(std::array<std::array<Cell, 20>,21>& outputMap, Pacman& pacman){
    char pacmanSpeed = 5;
    int indicator;
    bool wall1, wall2, wall3, wall4;
    wall1 = collision(false, false, position.x, position.y - pacmanSpeed, outputMap); //Check if the cell bove is wall
    wall2 = collision(false, false, position.x, position.y + pacmanSpeed, outputMap); //Check if the cell below is wall
    wall3 = collision(false, false, position.x - pacmanSpeed, position.y, outputMap); //Check if the cell to the left is wall
    wall4 = collision(false, false, position.x + pacmanSpeed, position.y, outputMap); //Check if the cell to the right is wall
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        if(wall1 == 0){
//            direction = 1;
            position.y -= pacmanSpeed;
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        if(wall2 == 0){
//            direction = 2;
            position.y += pacmanSpeed;
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        if(wall3 == 0){
//            direction = 3;
            position.x -= pacmanSpeed;
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        if (wall4 == 0){
//            direction = 4;
            position.x += pacmanSpeed;
        }
    }
    
    if(position.x <= -30){ //-30 as -cell size
        position.x = 570 - pacmanSpeed; //600 as the map width
    }
    else if(position.x >= 570){
        position.x = pacmanSpeed - 30;
    }
}
    
int Pacman::eatPellet(std::array<std::array<Cell, 20>,21>& outputMap, Pacman& pacman){
    char pacmanSpeed = 5;
    int indicator;
    int pelletEaten = 0;
    if (collision(true, false, position.x, position.y, outputMap) == false){
        pelletEaten += 1;
    }
    return pelletEaten;
}
    
    //PROBLEM HERE!!! Dont know where to call the collision function for 
    
    
    
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
//        indicator = 0;
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
//        indicator = 1;
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
//        indicator = 2;
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
//        indicator = 3;
//    }
//    switch (indicator) {
//        case 0:
//            position.y -= pacmanSpeed;
//            break;
//
//        case 1:
//        {
//            position.y += pacmanSpeed;
//
//            break;
//        }
//        case 2:
//        {
//            position.x -= pacmanSpeed;
//
//            break;
//        }
//        case 3:
//        {
//            position.x += pacmanSpeed;
//        }

    
    
void Pacman::initialPos(std::vector<std::string> map_script, Pacman& pacman){
    for (int a = 0; a < 21; a++)
    {
        for (int b = 0; b < 20; b++)
        {
            if (map_script[a][b] == 'P')
            {
                //                std::cout << a << b;
                pacman.setPosition(30*b, 30*a);
            }
        }
    }
}
