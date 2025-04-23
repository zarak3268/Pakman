#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include "../Agents/Agent.hpp"

const std::string MAP_TEXTURE_PATH = "assets/images/maze_parts.png";

class Maze {
    public:
        Maze(std::vector<std::vector<int>> map, int width, int height);
        ~Maze();
        void mitigateCollision(Agent& agent);
        void loadMazeTexture();
        void initWallFrames();
        void initWalls(std::vector<std::vector<int>> map, int width, int height);
        void draw(sf::RenderWindow& window);
    private:
        std::vector<std::vector<sf::RectangleShape*>> walls;
        std::vector<sf::IntRect> wallFrames;
        sf::Texture* mazeTexture;
};