#include <SFML/Graphics.hpp>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

	sf::CircleShape shape(50.f);
        sf::CircleShape rightEye(50.f);
        
    
        

// set the shape color to green
        rightEye.setFillColor(sf::Color(100,250,50));
        rightEye.setPosition(550, 120);
shape.setFillColor(sf::Color(100, 250, 50));
    shape.setPosition(150, 120);
        

        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(210,60));
        rectangle.setFillColor(sf::Color::Yellow);
        rectangle.setPosition(300, 440);
        window.draw(rectangle);
        
//        sf::CircleShape smile(150.f);
//        sf::CircleShape cover(150.f);
//
//        smile.setFillColor(sf::Color::Yellow);
//        cover.setFillColor(sf::Color::Black);
//
//        smile.setPosition(250, 250);
//        cover.setPosition(250, 200);
//
//        window.draw(smile);
//        window.draw(cover);
 window.draw(shape);
        window.draw(rightEye);
	// end the current frame
        window.display();
    }

    return 0;
}
