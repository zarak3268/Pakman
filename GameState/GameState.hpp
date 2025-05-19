#include <SFML/Graphics.hpp>

#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState {
    public:
        GameState() = default;
        virtual ~GameState() = default;
        virtual void loop(sf::RenderWindow* window) = 0;
};

#endif