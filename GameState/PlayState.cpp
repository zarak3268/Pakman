#include "PlayState.hpp"

PlayState::PlayState() {
    initMaze();
    initPellets();
    initCharacters();
}

void PlayState::initMaze() {
    maze = new Maze(MAP, WINDOW_SIZE.x, WINDOW_SIZE.y);
}

void PlayState::initPellets() {
    sf::Vector2f size = {WINDOW_SIZE.x/COLS, WINDOW_SIZE.y/ROWS};
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            sf::Vector2f position = {c*size.x + size.x/2, r*size.y + size.y/2};
            if (MAP[r][c] == -1) {
                pellets.push_back(new Pellet(position, size, PelletType::Small));
            } else if (MAP[r][c] == -2) {
                pellets.push_back(new Pellet(position, size, PelletType::Big));
            }
        }
    }
}

void PlayState::initCharacters() {
    pakman = new Pakman(PAKMAN_START_POSITION, maze->getTileSize(), CHARACTER_SPEED_NORMAL);
}

void PlayState::pollEvents(sf::RenderWindow* window) {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                pakman->setDirection(Direction::UP);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                pakman->setDirection(Direction::DOWN);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                pakman->setDirection(Direction::RIGHT);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                pakman->setDirection(Direction::LEFT);
        }
        if (event.type == sf::Event::Resized) {
            window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        }
    }
}

void PlayState::update(float dt) {
    maze->mitigateCollision(pakman);
    maze->wrap(pakman);
    maze->snap(pakman);
    pakman->eat(pellets);
    pakman->update(dt);
    for (Pellet* pellet : pellets) pellet->update(dt);
    if (pellets.empty()) gameOver = true;
}

void PlayState::draw(sf::RenderWindow* window) {
    window->clear(sf::Color::Black);
    maze->draw(window);
    for (Pellet* pellet : pellets) pellet->draw(window);
    pakman->draw(window);
    window->display();
}

void PlayState::loop(sf::RenderWindow* window) {
    while (window->isOpen() && !gameOver) {
        float dt = clock.restart().asSeconds();
        pollEvents(window);
        update(dt);
        draw(window);
    }
}

PlayState::~PlayState() {
    delete maze;
    delete pakman;
    for (Pellet* pellet : pellets) {
        delete pellet;
    }
    pellets.clear();
}