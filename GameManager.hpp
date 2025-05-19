#include <SFML/Graphics.hpp>
#include <stack>
#include "Config.hpp"
#include "GameState/GameState.hpp"
#include "GameState/PlayState.hpp"
#include "GameState/MainMenuState.hpp"
#include "GameState/GameOverState.hpp"

class GameManager {
    public:
        GameManager();
        void run();
    private:
        sf::RenderWindow* window;
        std::stack<std::unique_ptr<GameState>> states;
};