#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include "../Agents/Agent.hpp"

const std::string MAP_TEXTURE_PATH = "assets/images/maze_parts.png";

const std::vector<sf::IntRect> WALL_FRAMES = {
    {0, 27, 8, 8}, //Top right corner
    {9, 27, 8, 8}, //Top left corner
    {36, 27, 8, 8}, //Bottom right corner
    {45, 27, 8, 8}, //Bottom left corner
    {90, 27, 8, 8}, //Top horizontal
    {108, 27, 8, 8}, //Bottom horizontal
    {18, 27, 8, 8}, //Right vertical
    {27, 27, 8, 8}, //Left vertical
    {54, 45, 8, 8}, //Top right corner, single line
    {72, 45, 8, 8}, //Bottom right corner, single line
    {63, 45, 8, 8}, //Top left corner, single line
    {81, 45, 8, 8} //Bottom left corner, single line
};

class Maze {
    public:
        Maze(std::vector<std::vector<int>> map, int width, int height);
        ~Maze();
        void mitigateCollision(Agent& agent);
        void draw(sf::RenderWindow& window);
    private:
        std::vector<std::vector<sf::RectangleShape*>> walls;
        sf::Texture* mazeTexture;
};