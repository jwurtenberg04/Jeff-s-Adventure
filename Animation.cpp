#include "Animation.h"
#include <cassert>

namespace Animation {

int frame_at(sf::Time time, int fps, int frame_count) {
	return frame_at(time.toDuration(), fps, frame_count);
}

int frame_at(std::chrono::microseconds time, int fps, int frame_count) {
	using namespace std::literals::chrono_literals;
	std::chrono::microseconds frame_duration = 1'000'000us / fps;
	assert(frame_duration != 0us);
	auto frames_elapsed = time / frame_duration;
	auto frame_index = frames_elapsed % frame_count;
	assert(0 <= frame_index && frame_index < frame_count);
	return static_cast<int>(frame_index);
}

}
