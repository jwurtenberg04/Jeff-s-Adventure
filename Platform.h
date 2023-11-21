#pragma once

#include <optional>
#include <SFML/Graphics.hpp>

enum class Direction { left, right, top, bottom };

struct Collision {
	sf::FloatRect overlap;
	Direction from;
};

class Platform {
public:
	Platform(sf::Vector2f corner, sf::Vector2f size, sf::Color = sf::Color::Transparent);

	sf::FloatRect global_bounds() const { return shape.getGlobalBounds(); }
	sf::Color color() const { return shape.getOutlineColor(); }
	void set_color(sf::Color color);
	void draw(sf::RenderWindow&) const;
	std::optional<Collision> collide(const sf::FloatRect& hitbox) const;

private:
	sf::RectangleShape shape;
};
