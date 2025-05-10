#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <iostream>
#include <cmath>

Entity::Entity(sf::Vector2f position, sf::Vector2f size) {
    initialize(position, size);
}

void Entity::initialize(sf::Vector2f position, sf::Vector2f size) {
    this->setPosition(position);
    this->setSize(size);
    this->setOrigin(this->getSize().x/2, this->getSize().y/2);
}

void Entity::loadTexture(std::string path, sf::IntRect textureRect) {
    texture = new sf::Texture();
    texture->loadFromFile(path);
    this->setTexture(texture);
    this->setTextureRect(textureRect);
}

void Entity::setAnimation(Animation* animation) {
    this->animation = animation;
    this->setTextureRect(animation->getCurrentFrame());
}

std::pair<int, int> Entity::getGridPosition() {
    sf::Vector2f position = this->getPosition();
    sf::Vector2f size = this->getSize();
    position.x -= size.x/2;
    position.y -= size.y/2;
    int row = round(position.y/size.y);
    int col = round(position.x/size.x);
    return {row, col};
}

void Entity::update(float dt) {
    if (animation) {
        animation->update(dt);
        this->setTextureRect(animation->getCurrentFrame());
    }
}

void Entity::draw(sf::RenderWindow* window) {
    window->draw(*this);
}

Entity::~Entity() {
    if (texture) delete texture;
    if (animation) delete animation;
}