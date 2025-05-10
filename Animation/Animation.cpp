#include "Animation.hpp"

Animation::Animation(std::vector<std::vector<sf::IntRect>> frames, float switchTime) : frames(frames), switchTime(switchTime) {
    timeSinceLastSwtich = 0;
    currentFrameIdx.x = 0;
    currentFrameIdx.y = 0;
}

void Animation::setAnimationSequence(uint y) {
    currentFrameIdx.y = y;
}

sf::IntRect Animation::getCurrentFrame() {
    return frames[currentFrameIdx.y][currentFrameIdx.x];
}

void Animation::update(float dt) {
    timeSinceLastSwtich += dt;

    if (timeSinceLastSwtich >= switchTime) {
        timeSinceLastSwtich -= switchTime;
        currentFrameIdx.x = (currentFrameIdx.x + 1) % frames[0].size(); 
    }
}