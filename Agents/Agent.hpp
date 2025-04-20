#include <SFML/Graphics.hpp>
#include "Constants.hpp"

class Agent : public sf::RectangleShape {
    public:
        Agent(float speed = 250.0, Direction direction = Direction::RIGHT);
        void update(float dt);
        void setSpeed(float speed);
        void setDirection(Direction direction);
        void draw(sf::RenderWindow& window);
    private:
        float speed;
        Direction direction;
};