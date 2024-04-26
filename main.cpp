#include <SFML/Graphics.hpp>
#include <vector>
#include "PointMass.hpp"

int main()
{
    //Set up Before program loop
    const float defaultMass = 10.0f;
    const float defaultRadius = 10.0f;

    
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Solar Sistem Sim", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    std::vector<PointMass> objects;
    bool paused = true;


    //Program Loop
    while (window.isOpen())
    {
        //Events
        sf::Event event;
        sf::Vector2f clickPosition;
        while (window.pollEvent(event))
        {
            switch (event.type) 
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    clickPosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    objects.emplace_back(defaultRadius, defaultMass, clickPosition, sf::Vector2f(0.0f, 0.0f));
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code) 
                    {
                        case sf::Keyboard::Space:
                            paused = !paused;
                            break;
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        //Other Logic
        window.clear(sf::Color::Black);
        if (!paused) 
        {
            for (PointMass& object : objects) 
            {
                object.calcAcceleration(objects);
            }
            
            for (PointMass& object : objects)
            {
                object.move();
            }
           

        }

        for (PointMass& object : objects)
        {
            object.draw(window);
        }
        window.display();
    }

    return 0;
}