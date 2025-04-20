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
    float dt = 0;
    sf::Clock clock;

    while (window.isOpen()) {
        dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    agent.setDirection(Direction::UP);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    agent.setDirection(Direction::DOWN);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    agent.setDirection(Direction::RIGHT);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    agent.setDirection(Direction::LEFT);
            }
        }

        agent.update(dt);
        window.clear();
        agent.draw(window);
        window.display();
    }

    return 0;
}