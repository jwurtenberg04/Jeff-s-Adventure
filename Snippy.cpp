#include "Snippy.h"
#include <iostream>

int Snippy::generate() {
	if (!snippyIdleRight.loadFromFile("Snippy/Snippy-Right00.png")) {
		std::cerr << "Could not load Snippy-1.png.\n";
		return EXIT_FAILURE;
	}
	for (int i = 0; i < std::size(snippyRight); i++) {
		if (!snippyRightTextures[i].loadFromFile(snippyRight[i])) {
			std::cerr << "Could not load: " << snippyRight[i] << "\n";
			return EXIT_FAILURE;
		}
	}
	for (int i = 0; i < std::size(snippyLeft); i++) {
		if (!snippyLeftTextures[i].loadFromFile(snippyLeft[i])) {
			std::cerr << "Could not load: " << snippyLeft[i] << "\n";
			return EXIT_FAILURE;
		}
	}
	return 0;
}

void Snippy::draw(sf::RenderWindow &window, sf::View &view, int switch_control) {
	switch (switch_control) {
	case 1: {
		sprite.setPosition(sf::Vector2f{ pos_x, pos_y });
		sprite.setTexture(snippyRightTextures[animation_index]);
		window.draw(sprite);
		break;
	}
	case 2: {
		sprite.setPosition(sf::Vector2f{ pos_x, pos_y });
		sprite.setTexture(snippyLeftTextures[animation_index]);
		window.draw(sprite);
		break;
	}
	}
}

void Snippy::walk_right(sf::RenderWindow &window) {
	pos_x += walk_speed;
	animation_index = (animation_index + 1) % std::size(snippyRight);
}

void Snippy::walk_left(sf::RenderWindow &window) {
	pos_x -= walk_speed;
	animation_index = (animation_index + 1) % std::size(snippyLeft);
}
