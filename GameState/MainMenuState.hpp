#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "../Config.hpp"

const std::string TITLE_TEXTURE_PATH = "assets/images/pacman-logo.png";

class MainMenuState : public GameState {
    public:
        MainMenuState();
        void loop(sf::RenderWindow* window) override;
    private:
        std::unique_ptr<sf::Texture> titleTexture;
        sf::Sprite titleSprite;
        sf::Font font;
        sf::Text text;
        float textOpacity = 255;
        float fadeSpeed = -256;
        sf::Clock clock;
        float timeSinceLastIncrement = 0;

        bool startGame = false;

        void pollEvents(sf::RenderWindow* window);
        void update(float dt);
        void draw(sf::RenderWindow* window);
};