#include <SFML/Graphics.hpp>
#include "Character.hpp"
#include <iostream>
#include <cmath>

Character::Character(sf::Vector2f position, sf::Vector2f size, float speed) : Entity(position, size), speed(speed), direction(Direction::NONE) {
    loadTexture(CHARACTER_TEXTURES_FILE_PATH);
}

Direction Character::getDirection() {
    return direction;
}

float Character::getSpeed() {
    return speed;
}

void Character::setDirection(Direction direction) {
    this->direction = direction;
    if (animation) {
        if (direction == Direction::UP) {
            animation->setAnimationSequence(ANIMATION_UP);
        } else if (direction == Direction::DOWN) {
            animation->setAnimationSequence(ANIMATION_DOWN);
        } else if (direction == Direction::LEFT) {
            animation->setAnimationSequence(ANIMATION_LEFT);
        } else if (direction == Direction::RIGHT) {
            animation->setAnimationSequence(ANIMATION_RIGHT);
        }
    }
}

void Character::setSpeed(float speed) {
    this->speed = speed;
}

void Character::update(float dt) {
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