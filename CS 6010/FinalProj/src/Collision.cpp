//
//  Collision.cpp
//  testSFML
//
//  Created by Tailang  Cao on 9/20/23.
//

#include "Collision.hpp"
#include <array>
#include <cmath>

bool collision (bool collectPellet, bool useDoor, int x, int y, std::array<std::array<Cell, 20>,21>& outputMap){
    //get position of cell
    float cell_x = x / static_cast<float>(30);
    float cell_y = y / static_cast<float>(30);
    
    //get position of the interacting 4 cells
    for(int i = 0; i < 4 ; i++){
        int x;
        int y;
        switch(i){
            case(0):
            {
                x = floor(cell_x);
                y = floor(cell_y);
                break;
            }
                
            case(1):
            {
                x = floor(cell_x);
                y = ceil(cell_y);
                break;
            }
                
            case(2):
            {
                x = ceil(cell_x);
                y = floor(cell_y);
                break;
            }
                
            case(3):
            {
                x = ceil(cell_x);
                y = ceil(cell_y);
            }
        }
        if (x>=0 && x <= 20 && y >= 0 & y<=21){
            if (collectPellet == false && outputMap[x][y] == Cell::Wall){
                return true;
                }
            else if (collectPellet == true && outputMap[x][y] == Cell::Pellet){
                outputMap[x][y] = Cell::Empty;
                return false;
            }
            
//            }
//            else if (useDoor == false && outputMap[x][y] == Cell::Door){
//                return true;
//            }
//            else if (collectPellet == true){
               
//            }
        }
        
        
    }
    return false;
}
