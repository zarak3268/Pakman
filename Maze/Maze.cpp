#include "Maze.hpp"
#include "../utils/utils.h"
#include <iostream>
#include <cmath>

using namespace std;

Maze::Maze(vector<vector<int>> map, int width, int height) {
    loadMazeTexture();
    initWallFrames();
    initWalls(map, width, height);
}

void Maze::loadMazeTexture() {
    mazeTexture = new sf::Texture();
    mazeTexture->loadFromFile(MAP_TEXTURE_PATH);
}

void Maze::initWallFrames() {
    const int tileSize = 8;
    const int spacing = 1;
    const int rows = 3;
    const int columns = 16;

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            int left = x * (tileSize + spacing);
            int top = y * (tileSize + spacing);
            wallFrames.push_back({left, top, tileSize, tileSize});
        }
    }
}

void Maze::initWalls(vector<vector<int>> map, int width, int height) {
    rows = map.size();
    cols = map[0].size();
    cellWidth = width/cols;
    cellHeight = height/rows;
    this->map = map;
    this->width = width;
    this->height = height;
    walls = vector<vector<sf::RectangleShape*>>(rows, vector<sf::RectangleShape*>(cols, nullptr));

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int wallType = map[r][c];
            walls[r][c] = new sf::RectangleShape({cellWidth, cellHeight});
            walls[r][c]->setPosition(c*cellWidth + cellWidth/2, r*cellHeight + cellHeight/2);
            walls[r][c]->setOrigin(walls[r][c]->getSize().x/2, walls[r][c]->getSize().y/2);
            walls[r][c]->setOutlineColor(sf::Color::Red);
            walls[r][c]->setOutlineThickness(0.5);
            if (wallType >= 1) {    
                walls[r][c]->setTexture(mazeTexture);
                walls[r][c]->setTextureRect(wallFrames[wallType - 1]);
            }
        }
    }
}

bool Maze::canMove(Agent& agent) {
    std::pair<int, int> point = closestPoint(agent.getPosition());
    int r = point.first, c = point.second;
    if (agent.getDirection() == UP && map[r - 1][c] > 0 && getShortestDistance(agent, *walls[r - 1][c]) < 1) {
        return false;
    } else if (agent.getDirection() == DOWN && map[r + 1][c] > 0 && getShortestDistance(agent, *walls[r + 1][c]) < 1) {
        return false;
    } else if (agent.getDirection() == LEFT && map[r][c - 1] > 0 && getShortestDistance(agent, *walls[r][c - 1]) < 1) {
        return false;
    } else if (agent.getDirection() == RIGHT && map[r][c + 1] > 0 && getShortestDistance(agent, *walls[r][c + 1]) < 1) {
        return false;
    }
    return true;
}

void Maze::mitigateCollision(Agent& agent) {
    if (!canMove(agent)) agent.stop();
}

void Maze::bound(Agent& agent) {
    sf::Vector2f position = agent.getPosition();
    position.x = wrap(position.x, 0, width);
    position.y = wrap(position.y, 0, height);
    agent.setPosition(position);
}

std::pair<int, int> Maze::closestPoint(sf::Vector2f position) {
    position.x -= cellWidth/2;
    position.y -= cellHeight/2;
    int row = round(position.y/cellHeight);
    int col = round(position.x/cellWidth);
    return {row, col};
}

void Maze::snap(Agent& agent) {
    sf::Vector2f position = agent.getPosition();
    std::pair<int, int> point = closestPoint(position);
    int r = point.first;
    int c = point.second;
    if (agent.getDirection() == Direction::LEFT || agent.getDirection() == Direction::RIGHT) {
        position.y = walls[r][c]->getPosition().y;
    } else if (agent.getDirection() == Direction::UP || agent.getDirection() == Direction::DOWN) {
        position.x = walls[r][c]->getPosition().x;
    }
    agent.setPosition(position);
}

void Maze::draw(sf::RenderWindow& window) {
    for (vector<sf::RectangleShape*> vec : walls) {
        for (sf::RectangleShape* wall : vec) {
            if (wall) {
                window.draw(*wall);
            }
        }
    }
}

Maze::~Maze() {
    for (vector<sf::RectangleShape*> vec : walls) {
        for (sf::RectangleShape* wall : vec) {
            if (wall) delete wall;
        }
    }
    delete mazeTexture;
}