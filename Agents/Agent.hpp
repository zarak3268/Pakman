#include <SFML/Graphics.hpp>
#include "../Animation/Animation.hpp"
#include "Constants.hpp"

#ifndef AGENT_H
#define AGENT_H

const std::string AGENT_TEXTURES_FILE_PATH = "assets/images/agent_sprites.png";

const std::vector<std::vector<sf::IntRect>> FRAMES = {
    {{1, 0, 16, 16}, {17, 0, 16, 16}, {33, 0, 16, 16}},
    {{1, 16, 16, 16}, {17, 16, 16, 16}, {33, 0, 16, 16}},
    {{1, 32, 16, 16}, {17, 32, 16, 16}, {33, 0, 16, 16}},
    {{1, 48, 16, 16}, {17, 48, 16, 16}, {33, 0, 16, 16}}
};

const int PAKMAN_ANIMATION_RIGHT = 0;
const int PAKMAN_ANIMATION_LEFT = 1;
const int PAKMAN_ANIMATION_UP = 2;
const int PAKMAN_ANIMATION_DOWN = 3;

class Agent : public sf::RectangleShape {
    public:
        Agent(sf::Vector2f size, float speed);

        //getters
        Direction getDirection();

        //setters
        void setDirection(Direction direction);
        void setSpeed(float speed);

        //Member functions
        void moveReverse(float distance);
        void update(float dt);
        void draw(sf::RenderWindow* window);

        ~Agent();
    private:
        float speed;
        Direction direction;
        Animation animation;
        sf::Texture* texture;
};

#endif