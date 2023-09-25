#include <SFML/Graphics.hpp>
#include <iostream>

#include <chrono>
#include "Global.hpp"
#include "Pacman.hpp"
#include "ProcessScript.hpp"
#include "DrawMap.hpp"
#include "Ghost.hpp"
#include <thread>
#include <ctime>
#include <array>


int main()
{
//    make the game framerate-independent.
//    unsigned lag = 0;
//    unsigned frameDuration = 200000;
//    std::chrono::time_point<std::chrono::steady_clock> previous_time;
    
    
    // create the window
    sf::RenderWindow window(sf::VideoMode(600 , 630), "PacMan");
//    int cellSize = 30;
    bool gameOver = false;

    // run the program as long as the window is open
    std::vector<std::string> map_script={

    "####################",
    "#........G.........#",
    "#.#...#.####.###...#",
    "#.##.##.#....#  #..#",
    "#.#####.#....#   #.#",
    "#.#.#.#.#....#   #.#",
    "#.#.#.#.####.#   #.#",
    "#.#.#.#....#.#   #.#",
    "#.#...#....#.#  #..#",
    "#.#...#.####.###...#",
    "....................",
    "#.####.####.#.####.#",
    "#.#....#  #.#.#  #.#",
    "#.#....#  #.#.#  #.#",
    "#.####.#  #.#.#  #.#",
    "#.#  #.#  #.#.#  #.#",
    "#.#  #.#  #.#.#  #.#",
    "#.#  #.#  #.#.#  #.#",
    "#.####.####.#.####.#",
    "#..........P.......#",
    "####################"};
//
//
    Pacman pacman;
    Ghost ghost;
    ghost.initialPos(map_script, ghost);
    pacman.initialPos(map_script, pacman);
    std::array<std::array<Cell, 20>, 21> map;
    map = ProcessScript(map_script);
    
//    previous_time = std::chrono::steady_clock::now();
    
//    while (frameDuration <= lag)
//    {
//        //We decrease the lag.
//        lag -= frameDuration;
    window.setFramerateLimit(60);
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            
            
            ghost.update(map, ghost, pacman);
            pacman.update(map, pacman);
            int pelletEaten = pacman.eatPellet(map, pacman);
            
            //       std::cout << pacman.position.y << "\n";
            window.clear();
            drawMap(map, window);
            
            
            pacman.setPosition(pacman.getPosition().x, pacman.getPosition().y);
//            std::cout << "the current y position : " << pacman.getPosition().y << "\n";
            pacman.draw(window);
            ghost.setPosition(ghost.getPosition().x, ghost.getPosition().y);
            ghost.draw(window);
            
            if (ghost.getPosition().x > pacman.getPosition().x - 30 && ghost.getPosition().x < pacman.getPosition().x + 30){
                if (ghost.getPosition().y > pacman.getPosition().y - 30 && ghost.getPosition().y < pacman.getPosition().y + 30){
                    gameOver = true;
                }
            }
            
            if (gameOver) {
                sf::Texture gameOverTexture;
                if (!gameOverTexture.loadFromFile("/Users/tailangcao/myGithubRepo/FinalProj/src/gameover.png")) {
                    // 处理加载失败的情况
                }
                sf::Sprite gameOverSprite;
                gameOverSprite.setTexture(gameOverTexture);
                window.draw(gameOverSprite);
                window.display();
                std::this_thread::sleep_for(std::chrono::seconds(5));
                exit(1);
            }
            
            window.display();
            
            bool winGame = true;
            if(winGame){
                for(int a = 0; a < 20 ; a++){
                    for(int b = 0; b < 21; b++){
                        if(map[a][b] == Cell::Pellet){
                            winGame = false;
                            break;
                        }
                    }

                    if (winGame == false)
                    {
                        break;
                    }
                }

                if (winGame == true)
                {
                    sf::Texture gameOverTexture;
                    if (!gameOverTexture.loadFromFile("/Users/tailangcao/myGithubRepo/FinalProj/src/youwin.png")) {
                        // 处理加载失败的情况
                    }
                    
                    sf::Sprite gameOverSprite;
                    gameOverSprite.setTexture(gameOverTexture);
                    gameOverSprite.setPosition(0, 100);
                    window.draw(gameOverSprite);
                    window.display();
                    std::this_thread::sleep_for(std::chrono::seconds(8));
                    exit(1);
     //               window.clear();
                    
                    
                    exit(1);
                }
                    
                }
            
        }
        
        return 0;
    }
//   }
    

   
           





