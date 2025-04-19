#include <SFML/Graphics.hpp>
#include "Constants.hpp"

class Agent : public sf::RectangleShape {
    public:
        Agent(float speed = 1.0, Direction direction = Direction::RIGHT);
        void update(float dt);
        void setDirection(Direction direction);
        void setSpeed(float speed);
        void draw(sf::RenderWindow& window);
    private:
        float speed;
        Direction direction;
};