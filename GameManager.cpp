#include "GameManager.hpp"

GameManager::GameManager() : window(new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Pakman")) {
    states.push(std::make_unique<GameOverState>());
    states.push(std::make_unique<PlayState>());
    states.push(std::make_unique<MainMenuState>());
}

void GameManager::run() {
    while (!states.empty()) {
        states.top()->loop(window);
        states.pop();
    }
    window->close();
}