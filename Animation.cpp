#include "Animation.h"
#include <cassert>
#include <type_traits> // For `std::is_integral_v`

long animation_frame(sf::Time sample_time, long fps, long frame_count) {
	// Calculate how long each frame lasts.
	std::chrono::microseconds frame_duration { 1'000'000 / fps };
	std::chrono::microseconds time = sample_time.toDuration();
	// Wrap `time` back to 0 for each animation loop.
	time %= frame_duration * frame_count;
	// Get an integer frame index through truncating division.
	auto frame = time / frame_duration;
	// Double check that `frame` is an integer and in bounds.
	static_assert(std::is_integral_v<decltype(frame)>);
	assert(0 <= frame && frame < frame_count);
	return frame;
}
