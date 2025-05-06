#include "Pakman.hpp"
#include "../../utils/utils.hpp"

Pakman::Pakman(sf::Vector2f position, sf::Vector2f size, float speed) : Agent(position, size, speed) {
    this->loadTexture(AGENT_TEXTURES_FILE_PATH);
    this->setAnimation(new Animation(PAKMAN_FRAMES, 0.1));
}

int Pakman::eat(std::vector<Pellet*>& pellets) {
    int points = 0;
    for (int i = 0; i < pellets.size(); i++) {
        if (pellets[i]->getGridPosition() == this->getGridPosition()) {
            points = (pellets[i]->getType() == PelletType::Big) ? 50 : 10;
            delete pellets[i];
            pellets.erase(pellets.begin() + i);
            return points;
        }
    }
    return points;
}