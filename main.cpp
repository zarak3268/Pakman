#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    sf::RectangleShape shape({100, 100});
    shape.setOrigin(50, 50);
    shape.setPosition(300, 300);
    shape.setFillColor(sf::Color::Cyan);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    shape.move({0, -10});
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    shape.move({0, 10});
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    shape.move({10, 0});
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    shape.move({-10, 0});
            }
            
            
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}