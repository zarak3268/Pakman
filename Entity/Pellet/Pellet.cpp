#include <iostream>
#include "Pellet.hpp"

Pellet::Pellet(sf::Vector2f position, sf::Vector2f size, PelletType type) : Entity(position, size), type(type) {
    loadTexture(PELLET_TEXTURE_PATH, SMALL_PELLET_FRAME);
    if (type == PelletType::Big)
        setAnimation(new Animation(BIG_PELLET_FRAMES, 0.1));
}

PelletType Pellet::getType() {
    return type;
}