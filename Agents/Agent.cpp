#include <SFML/Graphics.hpp>
#include "../utils/utils.h"
#include "Agent.hpp"


Agent::Agent(float speed, sf::Texture* texture) : speed(speed), direction(Direction::RIGHT), animation(FRAMES, 0.1) {
    this->setSize({30, 30});
    this->setOrigin(15, 15);
    this->setTexture(texture);
    this->setTextureRect(animation.getCurrentFrame());
}

void Agent::setDirection(Direction direction) {
    this->direction = direction;
    if (direction == Direction::UP) {
        animation.setColumn(PAKMAN_ANIMATION_UP);
    } else if (direction == Direction::DOWN) {
        animation.setColumn(PAKMAN_ANIMATION_DOWN);
    } else if (direction == Direction::LEFT) {
        animation.setColumn(PAKMAN_ANIMATION_LEFT);
    } else {
        animation.setColumn(PAKMAN_ANIMATION_RIGHT);
    }
}

void Agent::setSpeed(float speed) {
    this->speed = speed;
}

void Agent::stop() {
    this->direction = Direction::NONE;
}

void Agent::update(float dt) {
    animation.update(dt);
    this->setTextureRect(animation.getCurrentFrame());

    sf::Vector2f offset(0,0);
    if (this->direction == Direction::UP) {
        offset.y = -1*speed*dt;
    } else if (this->direction == Direction::DOWN) {
        offset.y = speed*dt;
    } else if (this->direction == Direction::LEFT) {
        offset.x = -1*speed*dt;
    } else if (this->direction == Direction::RIGHT) {
        offset.x = speed*dt;
    }

    this->move(offset);
}

void Agent::moveReverse(float distance) {
    sf::Vector2f offset(0,0);
    if (this->direction == Direction::UP) {
        offset.y = distance;
    } else if (this->direction == Direction::DOWN) {
        offset.y = -1*distance;
    } else if (this->direction == Direction::LEFT) {
        offset.x = distance;
    } else if (this->direction == Direction::RIGHT) {
        offset.x = -1*distance;
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