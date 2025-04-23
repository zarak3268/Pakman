#include "Maze.hpp"
#include <iostream>

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
    int Y = map.size(), X = map[0].size();
    walls = vector<vector<sf::RectangleShape*>>(Y, vector<sf::RectangleShape*>(X, nullptr));
    sf::Vector2f wallSize = {width/X, height/Y};

    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            int wallType = map[y][x];
            if (wallType >= 1) {
                walls[y][x] = new sf::RectangleShape(wallSize);
                walls[y][x]->setTexture(mazeTexture);
                walls[y][x]->setTextureRect(wallFrames[wallType - 1]);
                walls[y][x]->setPosition(x*wallSize.x, y*wallSize.y);
            }
        }
    }
}

void Maze::mitigateCollision(Agent& agent) {
    for (vector<sf::RectangleShape*> vec : walls) {
        for (sf::RectangleShape* wall : vec) {
            if (wall && wall->getGlobalBounds().intersects(agent.getGlobalBounds())) {
                while (wall->getGlobalBounds().intersects(agent.getGlobalBounds()))
                    agent.moveReverse(1.0);
                agent.stop();
            }
        }
    }
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