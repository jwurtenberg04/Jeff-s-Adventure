#include "Platform.h"

Platform::Platform(sf::Vector2f corner, sf::Vector2f size, sf::Color color) {
	shape.setPosition(corner);
	shape.setSize(size);
	shape.setOutlineThickness(4.0f);
	set_color(color);
}

void Platform::set_color(sf::Color color) {
	shape.setOutlineColor(color);
	// Make the fill color partially transparent.
	shape.setFillColor({ color.r, color.g, color.b, 100 });
}

void Platform::draw(sf::RenderWindow& window) const {
	window.draw(shape);
}

std::optional<Collision> Platform::collide(const sf::FloatRect& hitbox) const {
	auto overlap = shape.getGlobalBounds().findIntersection(hitbox);
	if (!overlap) {
		// No overlap:
		return std::nullopt;
	}
	// Use the centers to determine the direction of the collision.
	const auto center = shape.getGlobalBounds().getCenter();
	const auto hitbox_center = hitbox.getCenter();
	Direction direction;
	if (overlap->size.x < overlap->size.y) {
		// If there is less horizontal overlap than vertical overlap,
		// consider the collision to be horizontal.
		const bool from_left = hitbox_center.x < center.x;
		direction = from_left ? Direction::left : Direction::right;
	} else {
		// Else, consider the collision to be vertical.
		const bool from_top = hitbox_center.y < center.y;
		direction = from_top ? Direction::top : Direction::bottom;
	}
	return Collision { *overlap, direction };
}
