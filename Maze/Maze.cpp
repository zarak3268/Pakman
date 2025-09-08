#include "Maze.hpp"
#include "../utils/utils.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Maze::Maze(const vector<vector<int>>& map, float width, float height) {
    loadMazeTexture();
    initWallFrames();
    initTiles(map, width, height);
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

void Maze::initTiles(const vector<vector<int>>& map, float width, float height) {
    rows = map.size();
    cols = map[0].size();
    tileWidth = width/cols;
    tileHeight = height/rows;
    this->width = width;
    this->height = height;
    tiles = vector<vector<Tile>>(rows, vector<Tile>(cols));

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int wallType = map[r][c];
            tiles[r][c] = Tile({tileWidth, tileHeight});
            tiles[r][c].setPosition(c*tileWidth + tileWidth/2, r*tileHeight + tileHeight/2);
            tiles[r][c].setOrigin(tiles[r][c].getSize().x/2, tiles[r][c].getSize().y/2);
            if (wallType >= 1) {
                tiles[r][c].setType(TileType::WALL);
                tiles[r][c].setTexture(mazeTexture);
                tiles[r][c].setTextureRect(wallFrames[wallType - 1]);
            } else {
                tiles[r][c].setFillColor(sf::Color::Black);
            }
        }
    }
}

sf::Vector2f Maze::getTileSize() {
    return {tileWidth, tileHeight};
}

std::pair<int, int> Maze::getGridPosition(sf::Vector2f position) {
    position.x -= tileWidth/2;
    position.y -= tileHeight/2;
    int row = round(position.y/tileHeight);
    int col = round(position.x/tileWidth);
    return {row, col};
}

bool Maze::canMove(Character* character) {
    std::pair<int, int> gridPosition = character->getGridPosition();
    int r = gridPosition.first, c = gridPosition.second;
    if (character->getDirection() == UP && tiles[r - 1][c].isWall() && getShortestDistance(character, &tiles[r - 1][c]) < 1) {
        return false;
    } else if (character->getDirection() == DOWN && tiles[r + 1][c].isWall() && getShortestDistance(character, &tiles[r + 1][c]) < 1) {
        return false;
    } else if (character->getDirection() == LEFT && tiles[r][c - 1].isWall() && getShortestDistance(character, &tiles[r][c - 1]) < 1) {
        return false;
    } else if (character->getDirection() == RIGHT && tiles[r][c + 1].isWall() && getShortestDistance(character, &tiles[r][c + 1]) < 1) {
        return false;
    }
    return true;
}

bool Maze::isWall(int row, int col) {
    return tiles[row][col].isWall();
}

bool Maze::withinBounds(int row, int col) {
    return row >= 0 && col >= 0 && row < tiles.size() && col < tiles[0].size();
}

void Maze::mitigateCollision(Character* character) {
    if (!canMove(character)) character->setDirection(Direction::NONE);
}

void Maze::wrap(Character* character) {
    auto f = [](float value, float min, float max) {
        float range = max - min;
        float wrapped = std::fmod(value - min, range);
        if (wrapped < 0) wrapped += range;
        return wrapped + min;
    };
    sf::Vector2f position = character->getPosition();
    position.x = f(position.x, 0, width);
    position.y = f(position.y, 0, height);
    character->setPosition(position);
}

void Maze::snap(Character* character) {
    sf::Vector2f position = character->getPosition();
    std::pair<int, int> gridPosition = character->getGridPosition();
    int r = gridPosition.first;
    int c = gridPosition.second;
    if (character->getDirection() == Direction::LEFT || character->getDirection() == Direction::RIGHT) {
        position.y = tiles[r][c].getPosition().y;
    } else if (character->getDirection() == Direction::UP || character->getDirection() == Direction::DOWN) {
        position.x = tiles[r][c].getPosition().x;
    }
    character->setPosition(position);
}

void Maze::draw(sf::RenderWindow* window) {
    for (vector<Tile> row : tiles) {
        for (Tile tile : row) {
            window->draw(tile);
        }
    }
}

Maze::~Maze() {
    delete mazeTexture;
}