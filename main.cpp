#include <SFML/Graphics.hpp>
#include <iostream>
#include "Agents/Agent.hpp"
#include "Agents/Constants.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    sf::Texture texture;
    texture.loadFromFile("assets/images/agent_sprites.png");
    
    Agent agent;
    agent.setTexture(&texture);
    agent.setTextureRect({PAKMAN_POS_X, PAKMAN_POS_Y, PAKMAN_WIDTH, PAKMAN_HEIGHT});

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    agent.move({0, -10});
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    agent.move({0, 10});
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    agent.move({10, 0});
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    agent.move({-10, 0});
            }
            
            
        }

        window.clear();
        agent.draw(window);
        window.display();
    }

    return 0;
}