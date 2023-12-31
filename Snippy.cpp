#include "Snippy.h"
#include <iostream>

int Snippy::generate(std::filesystem::path asset_dir) {
	if (!snippyIdleRight.loadFromFile((asset_dir / "Snippy/Snippy-Right00.png").string())) {
		std::cout << "Could not load Snippy-1.png. \n";
		return EXIT_FAILURE;
	}
	for (std::size_t i = 0; i < std::size(snippyRight); i++) {
		auto path = asset_dir / snippyRight[i];
		if (!snippyRightTextures[i].loadFromFile(path.string())) {
			std::cout << "Could not load: " << path.string() << "\n";
			return EXIT_FAILURE;
		}
	}
	for (std::size_t i = 0; i < std::size(snippyLeft); i++) {
		auto path = asset_dir / snippyLeft[i];
		if (!snippyLeftTextures[i].loadFromFile(path.string())) {
			std::cout << "Could not load: " << path << "\n";
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
