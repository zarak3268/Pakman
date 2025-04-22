#include "Maze.hpp"
#include <iostream>

using namespace std;

Maze::Maze(vector<vector<int>> map, int width, int height) {
    int Y = map.size(), X = map[0].size();
    mazeTexture = new sf::Texture();
    mazeTexture->loadFromFile(MAP_TEXTURE_PATH);
    walls = vector<vector<sf::RectangleShape*>>(Y, vector<sf::RectangleShape*>(X, nullptr));
    sf::Vector2f wallSize = {width/X, height/Y};

    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            int wallType = map[y][x];
            if (wallType >= 1 && wallType <= 9) {
                walls[y][x] = new sf::RectangleShape(wallSize);
                walls[y][x]->setTexture(mazeTexture);
                walls[y][x]->setTextureRect(WALL_FRAMES[wallType - 1]);
                walls[y][x]->setPosition(x*wallSize.x, y*wallSize.y);
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