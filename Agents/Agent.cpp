#include <SFML/Graphics.hpp>
#include "Agent.hpp"
#include "../utils/utils.h"
#include <iostream>

Agent::Agent(float speed, Direction direction) : speed(speed), direction(direction) {
    this->setSize({50, 50});
    this->setFillColor(sf::Color::Yellow);
    this->setOrigin(25, 25);
}

void Agent::setDirection(Direction direction) {
    this->direction = direction;
}

void Agent::setSpeed(float speed) {
    this->speed = speed;
}

void Agent::update(float dt) {
    this->setDirection(direction);

    sf::Vector2f offset(0,0);
    if (this->direction == Direction::UP) {
        offset.y = -1*speed*dt;
    } else if (this->direction == Direction::DOWN) {
        offset.y = speed*dt;
    } else if (this->direction == Direction::LEFT) {
        offset.x = -1*speed*dt;
    } else {
        offset.x = speed*dt;
    }

    this->move(offset);
}

void Agent::draw(sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f position = this->getPosition();
    position.x = wrap(position.x, 0, windowSize.x);
    position.y = wrap(position.y, 0, windowSize.y);
    this->setPosition(position);
    window.draw(*this);
}