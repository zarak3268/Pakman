#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <iostream>
#include "Agents/Agent.hpp"
#include "Agents/Constants.hpp"
#include "Maze/Maze.hpp"

const std::string AGENT_TEXTURES_FILE_PATH = "assets/images/agent_sprites.png";
const sf::Vector2f WINDOW_SIZE = {1008, 1023};
const sf::Vector2f PAKMAN_START_POSITION = {486, 775.5};
const int AGENT_SPEED_NORMAL = 250;

int main() {
    std::vector<std::vector<int>> map = {
        {  2, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 44, 43, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,  1 },
        {  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 26, 25,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3 },
        {  4,  0, 24, 15, 15, 23,  0, 24, 15, 15, 15, 23,  0, 26, 25,  0, 24, 15, 15, 15, 23,  0, 24, 15, 15, 23,  0,  3 },
        {  4,  0, 25,  0,  0, 26,  0, 25,  0,  0,  0, 26,  0, 26, 25,  0, 25,  0,  0,  0, 26,  0, 25,  0,  0, 26,  0,  3 },
        {  4,  0, 28, 21, 21, 27,  0, 28, 21, 21, 21, 27,  0, 28, 27,  0, 28, 21, 21, 21, 27,  0, 28, 21, 21, 27,  0,  3 },
        {  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3 },
        {  4,  0, 24, 15, 15, 23,  0, 24, 23,  0, 24, 15, 15, 15, 15, 15, 15, 23,  0, 24, 23,  0, 24, 15, 15, 23,  0,  3 },
        {  4,  0, 28, 21, 21, 27,  0, 26, 25,  0, 28, 21, 21, 36, 35, 21, 21, 27,  0, 26, 25,  0, 28, 21, 21, 27,  0,  3 },
        {  4,  0,  0,  0,  0,  0,  0, 26, 25,  0,  0,  0,  0, 26, 25,  0,  0,  0,  0, 26, 25,  0,  0,  0,  0,  0,  0,  3 },
        {  6, 13, 13, 13, 13, 23,  0, 26, 37, 15, 15, 23,  0, 26, 25,  0, 24, 15, 15, 38, 25,  0, 24, 13, 13, 13, 13,  5 },
        {  0,  0,  0,  0,  0,  4,  0, 26, 35, 21, 21, 27,  0, 28, 27,  0, 28, 21, 21, 36, 25,  0,  3,  0,  0,  0,  0,  0 },
        {  0,  0,  0,  0,  0,  4,  0, 26, 25,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 26, 25,  0,  3,  0,  0,  0,  0,  0 },
        {  0,  0,  0,  0,  0,  4,  0, 26, 25,  0, 30, 13, 34,  0,  0, 33, 13, 29,  0, 26, 25,  0,  3,  0,  0,  0,  0,  0 },
        { 11, 11, 11, 11, 11, 27,  0, 28, 27,  0,  3,  0,  0,  0,  0,  0,  0,  4,  0, 28, 27,  0, 28, 11, 11, 11, 11, 11 },
        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  0,  0,  0,  0,  0,  0,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
        { 13, 13, 13, 13, 13, 23,  0, 24, 23,  0,  3,  0,  0,  0,  0,  0,  0,  4,  0, 24, 23,  0, 24, 13, 13, 13, 13, 13 },
        {  0,  0,  0,  0,  0,  4,  0, 26, 25,  0, 32, 11, 11, 11, 11, 11, 11, 31,  0, 26, 25,  0,  3,  0,  0,  0,  0,  0 },
        {  0,  0,  0,  0,  0,  4,  0, 26, 25,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 26, 25,  0,  3,  0,  0,  0,  0,  0 },
        {  0,  0,  0,  0,  0,  4,  0, 26, 25,  0, 24, 15, 15, 15, 15, 15, 15, 23,  0, 26, 25,  0,  3,  0,  0,  0,  0,  0 },
        {  2, 11, 11, 11, 11, 27,  0, 28, 27,  0, 28, 21, 21, 36, 35, 21, 21, 27,  0, 28, 27,  0, 28, 11, 11, 11, 11,  1 },
        {  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 26, 25,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3 },
        {  4,  0, 24, 15, 15, 23,  0, 24, 15, 15, 15, 23,  0, 26, 25,  0, 24, 15, 15, 15, 23,  0, 24, 15, 15, 23,  0,  3 },
        {  4,  0, 28, 21, 36, 25,  0, 28, 21, 21, 21, 27,  0, 28, 27,  0, 28, 21, 21, 21, 27,  0, 26, 35, 21, 27,  0,  3 },
        {  4,  0,  0,  0, 26, 25,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 26, 25,  0,  0,  0,  3 },
        {  8, 15, 23,  0, 26, 25,  0, 24, 23,  0, 24, 15, 15, 15, 15, 15, 15, 23,  0,  24, 23, 0, 26, 25,  0, 24, 15,  7 },
        { 10, 21, 27,  0, 28, 27,  0, 26, 25,  0, 28, 21, 21, 36, 35, 21, 21, 27,  0,  26, 25, 0, 28, 27,  0, 28, 21,  9 },
        {  4,  0,  0,  0,  0,  0,  0, 26, 25,  0,  0,  0,  0, 26, 25,  0,  0,  0,  0,  26, 25, 0,  0,  0,  0,  0,  0,  3 },
        {  4,  0, 24, 15, 15, 15, 15, 38, 37, 15, 15, 23,  0, 26, 25,  0,  24, 15, 15, 38, 37, 15, 15, 15, 15, 23, 0,  3 },
        {  4,  0, 28, 21, 21, 21, 21, 21, 21, 21, 21, 27,  0, 28, 27,  0,  28, 21, 21, 21, 21, 21, 21, 21, 21, 27, 0,  3 },
        {  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3 },
        {  6, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,  5 }
    };

    std::cout << map.size() << ", " << map[0].size() << std::endl;

    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Pakman");
    sf::Texture texture;
    texture.loadFromFile(AGENT_TEXTURES_FILE_PATH);

    Maze maze(map, WINDOW_SIZE.x, WINDOW_SIZE.y);

    Agent agent(maze.getTileSize(), AGENT_SPEED_NORMAL, &texture);
    agent.setPosition(PAKMAN_START_POSITION);

    std::cout << "Agent size: " << agent.getSize().x << ", " << agent.getSize().y << std::endl;

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

        window.clear(sf::Color::White);
        maze.mitigateCollision(agent);
        agent.update(dt);
        maze.wrap(agent);
        maze.snap(agent);
        maze.draw(window);
        agent.draw(window);
        window.display();
    }

    return 0;
}