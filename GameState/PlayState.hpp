#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "../Entity/Characters/Pakman/Pakman.hpp"
#include "../Entity/Characters/Ghosts/Ghost.hpp"
#include "../Entity/Constants.hpp"
#include "../Maze/Maze.hpp"
#include "../Entity/Pellet/Pellet.hpp"
#include "../Config.hpp"

class PlayState : public GameState
{
public:
    PlayState();
    void loop(sf::RenderWindow *window) override;
    ~PlayState();

private:
    Maze *maze;
    std::vector<Pellet *> pellets;
    Pakman *pakman;
    Ghost *ghost;
    sf::Clock clock;
    bool gameOver = false;

    void initMaze();
    void initPellets();
    void initCharacters();
    void pollEvents(sf::RenderWindow *window);
    void update(float dt);
    void draw(sf::RenderWindow *window);
};