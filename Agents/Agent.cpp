#include <SFML/Graphics.hpp>
#include "Agent.hpp"
#include <iostream>

Agent::Agent(sf::Vector2f position, sf::Vector2f size, float speed) {
    initialize(position, size, speed);
}

void Agent::initialize(sf::Vector2f position, sf::Vector2f size, float speed) {
    this->setPosition(position);
    this->setSize(size);
    this->setOrigin(this->getSize().x/2, this->getSize().y/2);
    this->speed = speed;
    this->direction = Direction::RIGHT;
}

Direction Agent::getDirection() {
    return direction;
}

void Agent::setDirection(Direction direction) {
    this->direction = direction;
    if (animation) {
        if (direction == Direction::UP) {
            animation->setColumn(ANIMATION_UP);
        } else if (direction == Direction::DOWN) {
            animation->setColumn(ANIMATION_DOWN);
        } else if (direction == Direction::LEFT) {
            animation->setColumn(ANIMATION_LEFT);
        } else if (direction == Direction::RIGHT) {
            animation->setColumn(ANIMATION_RIGHT);
        }
    }
}

void Agent::setSpeed(float speed) {
    this->speed = speed;
}

void Agent::loadTexture(std::string path) {
    texture = new sf::Texture();
    texture->loadFromFile(path);
    this->setTexture(texture);
}

void Agent::setAnimation(Animation* animation) {
    this->animation = animation;
    this->setTextureRect(animation->getCurrentFrame());
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
    if (animation) {
        animation->update(dt);
        this->setTextureRect(animation->getCurrentFrame());
    }

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
    if (texture) delete texture;
    if (animation) delete animation;
}