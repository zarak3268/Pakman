#include <SFML/Graphics.hpp>
#include "../Animation/Animation.hpp"
#include "Constants.hpp"

#ifndef AGENT_H
#define AGENT_H

const int ANIMATION_RIGHT = 0;
const int ANIMATION_LEFT = 1;
const int ANIMATION_UP = 2;
const int ANIMATION_DOWN = 3;

class Agent : public sf::RectangleShape {
    public:
        Agent(sf::Vector2f position, sf::Vector2f size, float speed);

        //getters
        Direction getDirection();

        //setters
        void setDirection(Direction direction);
        void setSpeed(float speed);
        void loadTexture(std::string path);
        void setAnimation(Animation* animation);

        //Member functions
        void moveReverse(float distance);
        void update(float dt);
        void draw(sf::RenderWindow* window);

        ~Agent();
    private:
        float speed;
        Direction direction;
        Animation* animation = nullptr;
        sf::Texture* texture = nullptr;

        void initialize(sf::Vector2f position, sf::Vector2f size, float speed);
};

#endif