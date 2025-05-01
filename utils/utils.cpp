#include <cmath>
#include <SFML/Graphics.hpp>
#include "utils.hpp"

float wrap(float value, float min, float max) {
    float range = max - min;
    float wrapped = std::fmod(value - min, range);
    if (wrapped < 0) wrapped += range;
    return wrapped + min;
}

float getShortestDistance(const sf::RectangleShape* a, const sf::RectangleShape* b) {
    sf::FloatRect rectA = a->getGlobalBounds();
    sf::FloatRect rectB = b->getGlobalBounds();

    float dx = std::max(rectB.left - (rectA.left + rectA.width), rectA.left - (rectB.left + rectB.width));
    float dy = std::max(rectB.top - (rectA.top + rectA.height), rectA.top - (rectB.top + rectB.height));

    dx = std::max(dx, 0.f);
    dy = std::max(dy, 0.f);

    return std::sqrt(dx * dx + dy * dy);
}