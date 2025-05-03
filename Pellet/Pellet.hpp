#include <SFML/Graphics.hpp>
#include "../Animation/Animation.hpp"

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

class Pellet : public sf::RectangleShape{
    public:
        Pellet(PelletType type, sf::Vector2f position, std::pair<int, int> gridPosition, sf::Vector2f size);
        void loadTexture();
        void setupAnimation();
        PelletType getType();
        std::pair<int, int> getGridPosition();
        void update(float dt);
        void draw(sf::RenderWindow* window);
        ~Pellet();
    private:
        PelletType type;
        Animation* animation;
        sf::Texture* texture;
        std::pair<int, int> gridPosition;
};

#endif