#include "GameOverState.hpp"

GameOverState::GameOverState() {
    font.loadFromFile("assets/fonts/pacman-font.ttf");
    text.setFont(font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);
    text.setString("Game Over");
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    text.setPosition(0.5*WINDOW_SIZE.x, 0.56*WINDOW_SIZE.y);
}

void GameOverState::pollEvents(sf::RenderWindow* window) {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        if (event.type == sf::Event::Resized) {
            window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        }
    }
}

void GameOverState::loop(sf::RenderWindow* window) {
    window->draw(text);
    window->display();
    clock.restart();
    while (window->isOpen() && clock.getElapsedTime().asSeconds() < 3) {
        pollEvents(window);
    }
}