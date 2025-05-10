#include <SFML/Graphics.hpp>
#include "../Entity.hpp"
#include "../Constants.hpp"

#ifndef Character_H
#define Character_H

const int ANIMATION_RIGHT = 0;
const int ANIMATION_LEFT = 1;
const int ANIMATION_UP = 2;
const int ANIMATION_DOWN = 3;

class Character : public Entity {
    public:
        Character(sf::Vector2f position, sf::Vector2f size, float speed);

        //getters
        Direction getDirection();
        float getSpeed();

        //setters
        void setDirection(Direction direction);
        void setSpeed(float speed);

        //Member functions
        void update(float dt);
    private:
        float speed;
        Direction direction;
};

#endif