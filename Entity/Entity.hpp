#include <SFML/Graphics.hpp>
#include "../Animation/Animation.hpp"
#include "Constants.hpp"

#ifndef ENTITY_H
#define ENTITY_H

class Entity : public sf::RectangleShape {
    public:
        Entity(sf::Vector2f position = {0, 0}, sf::Vector2f size = {0, 0});

        //setters
        void loadTexture(std::string path, sf::IntRect textureRect = {0, 0, 0, 0});
        void setAnimation(Animation* animation);

        std::pair<int, int> getGridPosition();

        void update(float dt);
        void draw(sf::RenderWindow* window);

        ~Entity();
    protected:
        void initialize(sf::Vector2f position, sf::Vector2f size);
        sf::Texture* texture = nullptr;
        Animation* animation = nullptr;
};

#endif