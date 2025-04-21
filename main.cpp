#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include "Agents/Agent.hpp"
#include "Agents/Constants.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "Pakman");

    sf::Texture texture;
    texture.loadFromFile("assets/images/agent_sprites.png");
    
    Agent agent(250, &texture);
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
            if (event.type == sf::Event::Resized) {
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            }
        }

        agent.update(dt);
        window.clear();
        agent.draw(window);
        window.display();
    }

    return 0;
}