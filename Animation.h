#pragma once

#include <chrono>
#include <SFML/System.hpp>

namespace Animation {

// The returned index is always in the range `[0, frame_count)`.
int frame_at(sf::Time time, int fps, int frame_count);

// The returned index is always in the range `[0, frame_count)`.
int frame_at(std::chrono::microseconds time, int fps, int frame_count);

}
