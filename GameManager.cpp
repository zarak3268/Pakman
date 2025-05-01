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
                pellets.push_back(new Pellet(PelletType::Small, position, size));
            } else if (MAP[r][c] == -2) {
                pellets.push_back(new Pellet(PelletType::Big, position, size));
            }
        }
    }
}

void GameManager::initAgents() {
    agent = new Agent(maze->getTileSize(), AGENT_SPEED_NORMAL);
    agent->setPosition(PAKMAN_START_POSITION);
}

void GameManager::pollEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                agent->setDirection(Direction::UP);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                agent->setDirection(Direction::DOWN);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                agent->setDirection(Direction::RIGHT);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                agent->setDirection(Direction::LEFT);
        }
        if (event.type == sf::Event::Resized) {
            window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
        }
    }
}

void GameManager::update(float dt) {
    maze->mitigateCollision(agent);
    agent->update(dt);
    maze->wrap(agent);
    maze->snap(agent);
    for (Pellet* pellet : pellets) pellet->update(dt);
}

void GameManager::draw() {
    window->clear(sf::Color::White);
    maze->draw(window);
    for (Pellet* pellet : pellets) pellet->draw(window);
    agent->draw(window);
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
    delete agent;
    for (Pellet* pellet : pellets) {
        delete pellet;
    }
    pellets.clear();
}