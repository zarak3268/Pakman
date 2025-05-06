#include "GameManager.hpp"

GameManager::GameManager() {
    initWindow();
    initMaze();
    initPellets();
    initAgents();
}

void GameManager::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Pakman");
}

void GameManager::initMaze() {
    maze = new Maze(MAP, WINDOW_SIZE.x, WINDOW_SIZE.y);
}

void GameManager::initPellets() {
    sf::Vector2f size = {WINDOW_SIZE.x/COLS, WINDOW_SIZE.y/ROWS};
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            sf::Vector2f position = {c*size.x + size.x/2, r*size.y + size.y/2};
            if (MAP[r][c] == -1) {
                pellets.push_back(new Pellet(PelletType::Small, position, maze->getGridPosition(position), size));
            } else if (MAP[r][c] == -2) {
                pellets.push_back(new Pellet(PelletType::Big, position, maze->getGridPosition(position), size));
            }
        }
    }
}

void GameManager::initAgents() {
    pakman = new Pakman(PAKMAN_START_POSITION, maze->getTileSize(), AGENT_SPEED_NORMAL);
}

void GameManager::pollEvents() {
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

void GameManager::update(float dt) {
    maze->mitigateCollision(pakman);
    pakman->update(dt);
    maze->wrap(pakman);
    maze->snap(pakman);
    pakman->eat(pellets);
    for (Pellet* pellet : pellets) pellet->update(dt);
}

void GameManager::draw() {
    window->clear(sf::Color::Black);
    maze->draw(window);
    for (Pellet* pellet : pellets) pellet->draw(window);
    pakman->draw(window);
    window->display();
}

void GameManager::loop() {
    while (window->isOpen()) {
        float dt = clock.restart().asSeconds();
        pollEvents();
        update(dt);
        draw();
    }
}

GameManager::~GameManager() {
    delete window;
    delete maze;
    delete pakman;
    for (Pellet* pellet : pellets) {
        delete pellet;
    }
    pellets.clear();
}