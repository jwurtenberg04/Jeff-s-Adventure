#include "Eraser.h"

Eraser::Eraser(sf::Vector2f position, sf::Vector2f velocity)
	: position{ position }, velocity{ velocity }
{
	sprite.setTexture(texture);
}

void Eraser::draw(sf::RenderWindow &window) {
	sprite.setPosition(position);
	window.draw(sprite);
}

void Eraser::move() {
	position += velocity;
}

sf::Texture Eraser::texture{};

bool Eraser::load_texture() {
	return texture.loadFromFile("eraser.png");
}
