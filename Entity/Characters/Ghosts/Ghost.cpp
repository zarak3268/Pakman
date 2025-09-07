#include "Ghost.hpp"
#include "../../../utils/utils.hpp"

Ghost::Ghost(sf::Vector2f position, sf::Vector2f size, float speed) : Character(position, size, speed)
{
    setAnimation(new Animation(BLINKY_FRAMES, 0.1));
}
