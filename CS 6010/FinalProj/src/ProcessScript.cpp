//
//  ProcessScript.cpp
//  testSFML
//
//  Created by Tailang  Cao on 9/20/23.
//

#include "ProcessScript.hpp"
#include <iostream>
#include "Global.hpp"
#include <array>
#include <string>





std::array<std::array<Cell, 20>,21> ProcessScript (std::vector<std::string> map_script)
{
    std::array<std::array<Cell, 20>, 21> outputMap{};
    
    for (int a = 0; a < 21; a++)
    {
        for (int b = 0; b < 20; b++)
        {
            outputMap[b][a] = Cell::Empty;
            switch (map_script[a][b]) {
                    
                case '#':
                {
                    outputMap[b][a] = Cell::Wall;
                    break;
                }
                case '.':
                {
                    outputMap[b][a] = Cell::Pellet;
                    break;
                }
                case ' ':
                {
                    outputMap[b][a] = Cell::Empty;
                    break;
                }
//                case 'D':
//                {
//                    outputMap[b][a] = Cell::Door;
//                }
            }
        }
    }
    return outputMap;
}


