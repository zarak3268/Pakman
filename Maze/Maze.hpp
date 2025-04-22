#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

const std::string MAP_TEXTURE_PATH = "assets/images/maze_parts.png";

const std::vector<sf::IntRect> WALL_FRAMES = {
    {0, 27, 7, 8}, //Top right corner
    {8, 27, 7, 8}, //Top left corner
    {35, 27, 7, 8}, //Bottom right corner
    {44, 27, 7, 8}, //Bottom left corner
    {89, 27, 7, 8}, //Top horizontal
    {107, 27, 7, 8}, //Bottom horizontal
    {17, 27, 7, 8}, //Right vertical
    {26, 27, 7, 8} //Left vertical
};

class Maze {
    public:
        Maze(std::vector<std::vector<int>> map, int width, int height);
        ~Maze();
        void draw(sf::RenderWindow& window);
    private:
        std::vector<std::vector<sf::RectangleShape*>> walls;
        sf::Texture* mazeTexture;
};