#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "../Config.hpp"

class GameOverState : public GameState {
    public:
        GameOverState();
        void loop(sf::RenderWindow* window) override;
    private:
        sf::Font font;
        sf::Text text;
        sf::Clock clock;

        void pollEvents(sf::RenderWindow* window);
};