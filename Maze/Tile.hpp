#include <SFML/Graphics.hpp>

enum TileType {
    WALL,
    EMPTY
};

class Tile : public sf::RectangleShape {
    public:
        Tile(sf::Vector2f size = {0, 0}, TileType type = TileType::EMPTY);
        void setType(TileType type);
        bool isWall();
        bool isEmpty();
    private:
        TileType type;
};