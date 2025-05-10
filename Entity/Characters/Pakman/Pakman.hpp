#include "../Character.hpp"
#include "../../Pellet/Pellet.hpp"

const std::vector<std::vector<sf::IntRect>> PAKMAN_FRAMES = {
    {{1, 0, 16, 16}, {17, 0, 16, 16}, {33, 0, 16, 16}},
    {{1, 16, 16, 16}, {17, 16, 16, 16}, {33, 0, 16, 16}},
    {{1, 32, 16, 16}, {17, 32, 16, 16}, {33, 0, 16, 16}},
    {{1, 48, 16, 16}, {17, 48, 16, 16}, {33, 0, 16, 16}}
};

class Pakman : public Character {
    public:
        Pakman(sf::Vector2f position, sf::Vector2f size, float speed);
        int eat(std::vector<Pellet*>& pellets);
};