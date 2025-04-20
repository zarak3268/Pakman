#include <SFML/Graphics.hpp>

class Animation {
    public:
        Animation(std::vector<std::vector<sf::IntRect>> frames, float switchTime);
        void setColumn(uint y);
        sf::IntRect getCurrentFrame();
        void update(float dt);
    private:
        float timeSinceLastSwtich;
        float switchTime;
        sf::Vector2u currentFrameIdx;
        std::vector<std::vector<sf::IntRect>> frames;
};