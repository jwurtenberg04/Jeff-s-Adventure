#pragma once

#include <SFML/System.hpp>

// The returned frame index is always less than `frame_count`.
long animation_frame(sf::Time sample_time, long fps, long frame_count);
