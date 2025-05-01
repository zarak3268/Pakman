#include <SFML/Graphics.hpp>
#include "Agent.hpp"
#include <iostream>

Agent::Agent(sf::Vector2f size, float speed) : speed(speed), direction(Direction::RIGHT), animation(FRAMES, 0.1) {
    this->setSize(size);
    this->setOrigin(this->getSize().x/2, this->getSize().y/2);
    texture = new sf::Texture();
    texture->loadFromFile(AGENT_TEXTURES_FILE_PATH);
    this->setTexture(texture);
    this->setTextureRect(animation.getCurrentFrame());
}

Direction Agent::getDirection() {
    return direction;
}

void Agent::setDirection(Direction direction) {
    this->direction = direction;
    if (direction == Direction::UP) {
        animation.setColumn(PAKMAN_ANIMATION_UP);
    } else if (direction == Direction::DOWN) {
        animation.setColumn(PAKMAN_ANIMATION_DOWN);
    } else if (direction == Direction::LEFT) {
        animation.setColumn(PAKMAN_ANIMATION_LEFT);
    } else if (direction == Direction::RIGHT) {
        animation.setColumn(PAKMAN_ANIMATION_RIGHT);
    }
}

void Agent::setSpeed(float speed) {
    this->speed = speed;
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

void Agent::draw(sf::RenderWindow* window) {
    window->draw(*this);
}

Agent::~Agent() {
    delete texture;
}