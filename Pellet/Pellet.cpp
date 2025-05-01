#include <iostream>
#include "Pellet.hpp"

Pellet::Pellet(PelletType type, sf::Vector2f position, sf::Vector2f size) : type(type), animation(nullptr) {
    loadTexture();
    setupAnimation();
    this->setSize(size);
    this->setPosition(position);
    this->setOrigin(this->getSize().x/2, this->getSize().y/2);
    this->setOutlineColor(sf::Color::Red);
    this->setOutlineThickness(0.5);
}

void Pellet::loadTexture() {
    texture = new sf::Texture();
    texture->loadFromFile(PELLET_TEXTURE_PATH);
    this->setTexture(texture);
}

void Pellet::setupAnimation() {
    if (type == PelletType::Small)
        this->setTextureRect(SMALL_PELLET_FRAME);
    else
        animation = new Animation(BIG_PELLET_FRAMES, 0.1);
}

void Pellet::update(float dt) {
    if (animation) {
        animation->update(dt);
        this->setTextureRect(animation->getCurrentFrame());
    }
}

void Pellet::draw(sf::RenderWindow* window) {
    window->draw(*this);
}

Pellet::~Pellet() {
    if (animation) delete animation;
    delete texture;
}