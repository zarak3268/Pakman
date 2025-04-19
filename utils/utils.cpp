#include <cmath>
#include "utils.h"

float wrap(float value, float min, float max) {
    float range = max - min;
    float wrapped = std::fmod(value - min, range);
    if (wrapped < 0) wrapped += range;
    return wrapped + min;
}