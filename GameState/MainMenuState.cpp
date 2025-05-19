#include "MainMenuState.hpp"
#include <algorithm>
#include <iostream>

MainMenuState::MainMenuState() {
    titleTexture = std::make_unique<sf::Texture>();
    titleTexture->loadFromFile(TITLE_TEXTURE_PATH);
    titleSprite.setTexture(*titleTexture);
    titleSprite.setScale({0.5, 0.5});
    sf::FloatRect bounds = titleSprite.getLocalBounds();
    titleSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    titleSprite.setPosition(0.5*WINDOW_SIZE.x, 0.25*WINDOW_SIZE.y);
    font.loadFromFile("assets/fonts/pacman-font.ttf");
    text.setFont(font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color(255, 255, 255, textOpacity));
    text.setString("Press enter to play");
    bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    text.setPosition(0.5*WINDOW_SIZE.x, 0.5*WINDOW_SIZE.y);
    // titleSprite.setColor(sf::Color(255, 255, 255, 200));
}

void MainMenuState::pollEvents(sf::RenderWindow* window) {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                startGame = true;
        }
        if (event.type == sf::Event::Resized) {
            window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        }
    }
}

void MainMenuState::update(float dt) {
    timeSinceLastIncrement += dt;
    if (textOpacity >= 255 || textOpacity <= 0)
        fadeSpeed *= -1.0;
    textOpacity += fadeSpeed * dt;
    if (fadeSpeed > 0)
        textOpacity = std::min(textOpacity, 255.0f);
    else
        textOpacity = std::max(textOpacity, 0.0f);
    text.setFillColor(sf::Color(255, 255, 255, textOpacity));
}

void MainMenuState::draw(sf::RenderWindow* window) {
    window->clear();
    window->draw(titleSprite);
    window->draw(text);
    window->display();
}

void MainMenuState::loop(sf::RenderWindow* window) {
    while (window->isOpen() && !startGame) {
        float dt = clock.restart().asSeconds();
        pollEvents(window);
        update(dt);
        draw(window);
    }
}