#include "Platform.h"

Platform::Platform(sf::Vector2f corner, sf::Vector2f size, sf::Color color) {
	rectangle.setPosition(corner);
	rectangle.setSize(size);
	rectangle.setOutlineThickness(4.0f);
	set_color(color);
}

void Platform::set_color(sf::Color color) {
	rectangle.setOutlineColor(color);
	// Make the fill color partially transparent.
	rectangle.setFillColor({ color.r, color.g, color.b, 100 });
}

void Platform::draw(sf::RenderWindow& window) const {
	window.draw(rectangle);
}

std::optional<Collision> Platform::collide(const sf::FloatRect& other) const {
	sf::FloatRect overlap;
	if (!rectangle.getGlobalBounds().intersects(other, overlap)) {
		// No overlap:
		return std::nullopt;
	}
	// Just use position to guess the direction of the collision.
	const auto center = rectangle.getPosition() + rectangle.getSize() / 2.0f;
	const auto other_center = other.getPosition() + other.getSize() / 2.0f;
	Direction direction;
	if (overlap.width < overlap.height) {
		// If there is less horizontal overlap than vertical overlap,
		// consider this collision to be horizontal.
		bool from_left = other_center.x < center.x;
		direction = from_left ? Direction::left : Direction::right;
	} else {
		// Otherwise, consider this collision to be vertical.
		bool from_top = other_center.y < center.y;
		direction = from_top ? Direction::top : Direction::bottom;
	}
	return Collision{ overlap, direction };
}
