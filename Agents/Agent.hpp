#include <SFML/Graphics.hpp>
#include "../Animation/Animation.hpp"
#include "Constants.hpp"

const std::vector<std::vector<sf::IntRect>> FRAMES = {
    {{0, 0, 16, 16}, {16, 0, 16, 16}, {32, 0, 16, 16}},
    {{0, 16, 16, 16}, {16, 16, 16, 16}, {32, 0, 16, 16}},
    {{0, 32, 16, 16}, {16, 32, 16, 16}, {32, 0, 16, 16}},
    {{0, 48, 16, 16}, {16, 48, 16, 16}, {32, 0, 16, 16}}
};

const int PAKMAN_ANIMATION_RIGHT = 0;
const int PAKMAN_ANIMATION_LEFT = 1;
const int PAKMAN_ANIMATION_UP = 2;
const int PAKMAN_ANIMATION_DOWN = 3;

class Agent : public sf::RectangleShape {
    public:
        Agent(float speed, sf::Texture* texture);
        void update(float dt);
        void setSpeed(float speed);
        void setDirection(Direction direction);
        void draw(sf::RenderWindow& window);
    private:
        float speed;
        Direction direction;
        Animation animation;
};