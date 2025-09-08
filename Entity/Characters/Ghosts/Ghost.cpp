#include "Ghost.hpp"
#include "../../../utils/utils.hpp"
#include <limits>
#include <iostream>

Ghost::Ghost(sf::Vector2f position, sf::Vector2f size, float speed) : Character(position, size, speed)
{
    setAnimation(new Animation(BLINKY_FRAMES, 0.1));
}

void Ghost::chase(Maze* maze, Character* pacman) {

    // Get valid directions (not reversing and not walls)
    std::vector<Direction> possibleDirections = getValidDirections(maze);

    // Target Pac-Man's current grid position
    auto [targetRow, targetCol] = maze->getGridPosition(pacman->getPosition());

    // Pick the direction that minimizes distance to target
    Direction bestDir = Direction::NONE;
    float minDist = std::numeric_limits<float>::infinity();

    for (Direction dir : possibleDirections) {
        sf::Vector2f nextPos = nextTilePosition(dir, maze);
        auto [nextRow, nextCol] = maze->getGridPosition(nextPos);

        float dist = std::abs(nextRow - targetRow) + std::abs(nextCol - targetCol); // Manhattan distance
        if (dist < minDist) {
            minDist = dist;
            bestDir = dir;
        }
    }
    
    std::cout << "Direction: " << bestDir << std::endl;

    if (bestDir != Direction::NONE)
        setDirection(bestDir);
}

bool Ghost::isAtIntersection(Maze* maze) {
    auto [row, col] = maze->getGridPosition(getPosition());
    int freeCount = 0;
    for (Direction dir : {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT}) {
        sf::Vector2f pos = nextTilePosition(dir, maze);
        auto [r, c] = maze->getGridPosition(pos);
        if (maze->withinBounds(r, c) && !maze->isWall(r, c))
            freeCount++;
    }
    return freeCount > 2; // Intersection if 3+ directions are free
}

std::vector<Direction> Ghost::getValidDirections(Maze* maze) {
    std::vector<Direction> dirs;
    for (Direction dir : {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT}) {
        if (dir == oppositeDirection(getDirection())) continue;

        sf::Vector2f pos = nextTilePosition(dir, maze);
        auto [row, col] = maze->getGridPosition(pos);
        if (maze->withinBounds(row, col) && !maze->isWall(row, col))
            dirs.push_back(dir);
    }
    return dirs;
}

sf::Vector2f Ghost::nextTilePosition(Direction dir, Maze* maze) {
    sf::Vector2f pos = getPosition();
    sf::Vector2f tileSize = maze->getTileSize();
    switch (dir) {
        case Direction::UP:    pos.y -= tileSize.y; break;
        case Direction::DOWN:  pos.y += tileSize.y; break;
        case Direction::LEFT:  pos.x -= tileSize.x; break;
        case Direction::RIGHT: pos.x += tileSize.x; break;
        default: break;
    }
    return pos;
}

Direction Ghost::oppositeDirection(Direction dir) {
    switch (dir) {
        case Direction::UP: return Direction::DOWN;
        case Direction::DOWN: return Direction::UP;
        case Direction::LEFT: return Direction::RIGHT;
        case Direction::RIGHT: return Direction::LEFT;
        default: return Direction::NONE;
    }
}