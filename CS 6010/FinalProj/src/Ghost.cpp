//
//  Ghost.cpp
//  testSFML
//
//  Created by Tailang  Cao on 9/21/23.
//

#include "Ghost.hpp"

Ghost::Ghost(){
    direction = 0;
    position.x = 0;
    position.y = 0;
    ghostSpeed = 3;
}

Position Ghost::getPosition(){
    return position;
}

void Ghost::setPosition(int x, int y){
    position.x = x;
    position.y = y;
}

void Ghost::initialPos(std::vector<std::string> map_script, Ghost& ghost){
    for (int a = 0; a < 21; a++)
    {
        for (int b = 0; b < 20; b++)
        {
            if (map_script[a][b] == 'G')
            {
                //                std::cout << a << b;
                ghost.setPosition(30*b, 30*a);
            }
        }
    }
}

void Ghost::draw(sf::RenderWindow& myWindow){
    if (!texture.loadFromFile("/Users/tailangcao/myGithubRepo/FinalProj/src/blinky.png")) {
        // 处理加载失败的情况
        // 可以选择使用默认图像或输出错误消息
    }
    sprite.setTexture(texture);
    sprite.setPosition(position.x, position.y);
    myWindow.draw(sprite);
    
}


float Ghost::getDistance (int direction, Pacman pacman){
    int x = position.x;
    int y = position.y;
    float distance;
    
    switch (direction){
        case 0:
        {
            y -= ghostSpeed;
            break;
        }
        case 1:
        {
            x += ghostSpeed;
            break;
        }
        case 2:
        {
            y += ghostSpeed;
            break;
        }
        case 3:
        {
            x -= ghostSpeed;
        }
    }
    distance = sqrt((pow((x - pacman.getPosition().x),2) + pow((y - pacman.getPosition().y), 2)));
    return distance;
}


void Ghost::update(std::array<std::array<Cell, 20>, 21>& outputMap, Ghost& ghost, Pacman& pacman){
    int availableWays = 0; //greater than 1 if getting to intersaction point
    int optimalDirection = 4;
    
    std::array<bool, 4> wall{};
    wall[0] = collision(false, false, position.x, position.y - ghostSpeed, outputMap);
    wall[1] = collision(false, false, position.x + ghostSpeed, position.y, outputMap);
    wall[2] = collision(false, false, position.x, position.y + ghostSpeed, outputMap);
    wall[3] = collision(false, false, position.x - ghostSpeed, position.y, outputMap);
    
    for (int a = 0; a < 4; a++){
        if (a == (2 + direction) % 4){
            continue; //remove the sircumstance of the optimal direction is the one that is moving back
        }
        else if (wall[a] == 0){
            availableWays++;
            if(optimalDirection == 4){
                optimalDirection = a;
            }
            if(getDistance(a,pacman) < getDistance(optimalDirection,pacman))
            {
                optimalDirection = a;
            }
        }
        
    }
    
    if (availableWays > 1){
        direction = optimalDirection;
    }
    else{
        if(optimalDirection == 4){
            direction = (direction + 2) % 4;
        }
    }
    
    switch (direction) {
        case 0:
        {
            position.y -= ghostSpeed;
            break;
        }
        case 1:
        {
            position.x += ghostSpeed;
            break;
        }
        case 2:
        {
            position.y += ghostSpeed;
            break;
        }
        case 3:
        {
            position.x -= ghostSpeed;
        }
    }
    
    if(position.x <= -30){ //-30 as -cell size
        position.x = 570 - ghostSpeed; //600 as the map width
    }
    else if(position.x >= 570){
        position.x = ghostSpeed - 30;
    }
    
}
