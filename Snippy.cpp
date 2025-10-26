#include "Snippy.h"
#include <iostream>
#include "Animation.h"

int Snippy::generate(const std::filesystem::path& asset_dir) {
	auto path = asset_dir / "Snippy/Snippy-Right00.png";
	if (!snippyIdleRight.loadFromFile(path)) {
		std::cerr << "Could not load: " << path << '\n';
		return EXIT_FAILURE;
	}
	for (std::size_t i = 0; i < std::size(snippyRight); i++) {
		auto path = asset_dir / snippyRight[i];
		if (!snippyRightTextures[i].loadFromFile(path)) {
			std::cerr << "Could not load: " << path << '\n';
			return EXIT_FAILURE;
		}
	}
	for (std::size_t i = 0; i < std::size(snippyLeft); i++) {
		auto path = asset_dir / snippyLeft[i];
		if (!snippyLeftTextures[i].loadFromFile(path)) {
			std::cerr << "Could not load: " << path << '\n';
			return EXIT_FAILURE;
		}
	}
	return 0;
}

void Snippy::draw(sf::RenderWindow &window, sf::View &view, int switch_control) {
	switch (switch_control) {
	case 1: {
		int animation_index = current_frame(std::size(snippyRightTextures));
		sf::Sprite sprite { snippyRightTextures[animation_index] };
		sprite.setPosition(sf::Vector2f{ pos_x, pos_y });
		window.draw(sprite);
		break;
	}
	case 2: {
		int animation_index = current_frame(std::size(snippyLeftTextures));
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

int Snippy::current_frame(int frame_count) const {
	constexpr int fps = 60;
	return Animation::frame_at(animation_clock.getElapsedTime(), fps, frame_count);
}
