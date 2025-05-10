#include <SFML/Graphics.hpp>
#include "../Entity.hpp"

#ifndef PELLET_H
#define PELLET_H

const std::string PELLET_TEXTURE_PATH = "assets/images/maze_parts.png";

enum PelletType {
    Small,
    Big
};

const std::vector<std::vector<sf::IntRect>> BIG_PELLET_FRAMES = {
    {{126, 18, 8, 8}, {135, 18, 8, 8}},
};

const sf::IntRect SMALL_PELLET_FRAME = {117, 18, 8, 8};

class Pellet : public Entity {
    public:
        Pellet(sf::Vector2f position, sf::Vector2f size, PelletType type);
        PelletType getType();
    private:
        PelletType type;
};

#endif