#include <SFML/Graphics.hpp>
#include "Agent.hpp"
#include "../utils/utils.h"

Agent::Agent(float speed, Direction direction) : speed(speed), direction(direction) {
    this->setSize({50, 50});
    this->setFillColor(sf::Color::Yellow);
}

void Agent::setDirection(Direction direction) {
    this->direction = direction;
}

void Agent::setSpeed(float speed) {
    this->speed = speed;
}

void Agent::draw(sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f position = this->getPosition();
    position.x = wrap(position.x, 0, windowSize.x);
    position.y = wrap(position.y, 0, windowSize.y);
    this->setPosition(position);
    window.draw(*this);
}