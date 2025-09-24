#include "Eraser.h"

Eraser::Eraser(sf::Vector2f position, sf::Vector2f velocity)
	: position { position }, velocity { velocity } { }

void Eraser::draw(sf::RenderWindow &window) {
	sf::Sprite sprite { texture };
	sprite.setPosition(position);
	window.draw(sprite);
}

void Eraser::move(sf::Time dt) {
	position += velocity * dt.asSeconds();
}

void Eraser::draw_debug(sf::RenderWindow &window) {
	sf::Sprite sprite {texture};
	auto bounds = sprite.getGlobalBounds();
	sf::RectangleShape shape { bounds.size };
	shape.setPosition(bounds.position);
	shape.setOutlineThickness(4.0f);
	shape.setOutlineColor(sf::Color::Magenta);
	shape.setFillColor(sf::Color::Transparent);
	window.draw(shape);
}

sf::FloatRect Eraser::getRect() {
	sf::Sprite sprite { texture };
	return sprite.getGlobalBounds();
}
sf::Texture Eraser::texture{};

bool Eraser::load_texture(const std::filesystem::path& asset_dir) {
	return texture.loadFromFile(asset_dir / "eraser.png");

	
}
