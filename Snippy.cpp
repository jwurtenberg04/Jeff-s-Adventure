#include "Snippy.h"
#include "Animation.h"
#include <iostream>

int Snippy::generate(const std::filesystem::path& asset_dir) {
	auto path = asset_dir / "Snippy/Snippy-Right00.png";
	if (!snippyIdleRight.loadFromFile(path)) {
		std::cout << "Could not load: " << path << '\n';
		return EXIT_FAILURE;
	}
	for (std::size_t i = 0; i < std::size(snippyRight); i++) {
		auto path = asset_dir / snippyRight[i];
		if (!snippyRightTextures[i].loadFromFile(path)) {
			std::cout << "Could not load: " << path << '\n';
			return EXIT_FAILURE;
		}
	}
	for (std::size_t i = 0; i < std::size(snippyLeft); i++) {
		auto path = asset_dir / snippyLeft[i];
		if (!snippyLeftTextures[i].loadFromFile(path)) {
			std::cout << "Could not load: " << path << '\n';
			return EXIT_FAILURE;
		}
	}
	return 0;
}

void Snippy::draw(sf::RenderWindow &window, sf::View &view, int switch_control) {
	switch (switch_control) {
	case 1: {
		auto animation_index = current_frame(std::size(snippyRightTextures));
		sf::Sprite sprite { snippyRightTextures[animation_index] };
		sprite.setPosition(sf::Vector2f{ pos_x, pos_y });
		window.draw(sprite);
		break;

	}
	case 2: {
		auto animation_index = current_frame(std::size(snippyLeftTextures));
		sf::Sprite sprite { snippyLeftTextures[animation_index] };
		sprite.setPosition(sf::Vector2f{ pos_x, pos_y });
		window.draw(sprite);
		break;
	}
	case 3:
		break;
	}

}

void Snippy::walk_right(sf::Time dt) {
	pos_x += walk_speed * dt.asSeconds();
}

void Snippy::walk_left(sf::Time dt) {
	pos_x -= walk_speed * dt.asSeconds();
}

sf::FloatRect Snippy::global_bounds() const {
	return { { pos_x, pos_y }, hitbox_size };
}

long Snippy::current_frame(long frame_count) const {
	constexpr long fps = 60;
	return animation_frame(animation_clock.getElapsedTime(), fps, frame_count);
}
