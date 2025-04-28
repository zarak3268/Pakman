#include "Tile.hpp"

Tile::Tile(sf::Vector2f size, TileType type) : type(type) {
    this->setSize(size);
}

void Tile::setType(TileType type) {
    this->type = type;
}

bool Tile::isEmpty() {
    return type == TileType::EMPTY;
}

bool Tile::isWall() {
    return type == TileType::WALL;
}