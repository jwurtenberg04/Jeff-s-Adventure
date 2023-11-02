#include "Snippy.h"

int Snippy::generate() {
	if (!snippyIdleRight.loadFromFile("Snippy-1.png")) return EXIT_FAILURE;
	return 0;
}

void Snippy::draw(sf::RenderWindow &window, sf::View &view, int &switch_control) {
	sprite.setPosition(sf::Vector2f{ pos_x, pos_y });
	sprite.setTexture(snippyIdleRight);
	window.draw(sprite);
}