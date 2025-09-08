#include "../Character.hpp"
#include "../../../Maze/Maze.hpp"

enum GhostState {
    CHASE,
    FLEE
};

const std::vector<std::vector<sf::IntRect>> BLINKY_FRAMES = {
    {{2, 64, 16, 16}, {18, 64, 16, 16}},
    {{34, 64, 16, 16}, {50, 64, 16, 16}},
    {{66, 64, 16, 16}, {82, 64, 16, 16}},
    {{98, 64, 16, 16}, {114, 64, 16, 16}}};

class Ghost : public Character
{
public:
    Ghost(sf::Vector2f position, sf::Vector2f size, float speed);
    void chase(Maze* maze, Character* pacman);

private:
    bool isAtIntersection(Maze* maze);
    std::vector<Direction> getValidDirections(Maze* maze);
    sf::Vector2f nextTilePosition(Direction dir, Maze* maze);
    Direction oppositeDirection(Direction dir);
};