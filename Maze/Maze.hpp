#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include "../Entity/Characters/Character.hpp"
#include "Tile.hpp"

const std::string MAP_TEXTURE_PATH = "assets/images/maze_parts.png";

class Maze {
    public:
        Maze(const std::vector<std::vector<int>>& map, float width, float height);
        void loadMazeTexture();
        void initWallFrames();
        void initTiles(const std::vector<std::vector<int>>& map, float width, float height);

        sf::Vector2f getTileSize();

        std::pair<int, int> getGridPosition(sf::Vector2f position);
        bool canMove(Character* character);
        void mitigateCollision(Character* character);
        void wrap(Character* character);
        void snap(Character* character);
        void draw(sf::RenderWindow* window);

        ~Maze();
    private:
        int rows;
        int cols;
        float width;
        float height;
        float tileWidth;
        float tileHeight;
        std::vector<std::vector<Tile>> tiles;
        std::vector<sf::IntRect> wallFrames;
        sf::Texture* mazeTexture;
};