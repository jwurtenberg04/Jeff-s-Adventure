#include "Jeff.h"

int Jeff::generate(const std::filesystem::path& asset_dir) {
	if (!jeff_standing_texture.loadFromFile((asset_dir / jeff_standing).string())) return EXIT_FAILURE;
	if (!jeff_standing_left_texture.loadFromFile((asset_dir / jeff_standing_left).string())) return EXIT_FAILURE;
	for (std::size_t i = 0; i < std::size(jeff_walking); i++) {
		if (!jeff_walking_textures[i].loadFromFile((asset_dir / jeff_walking[i]).string()))
			return EXIT_FAILURE;
	}
	for (std::size_t i = 0; i < std::size(jeff_walking_left); i++) {
		if (!jeff_walking_left_textures[i].loadFromFile((asset_dir / jeff_walking_left[i]).string()))
			return EXIT_FAILURE;
	}
	for (std::size_t i = 0; i < std::size(jeff_shooting); i++) {
		if (!jeff_shooting_textures[i].loadFromFile((asset_dir / jeff_shooting[i]).string()))
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void Jeff::walk_right(sf::RenderWindow &window, float direction) {
	pos_x += direction * walk_speed;
	animation_index = (animation_index + 1) % std::size(jeff_walking);
}

void Jeff::walk_left(sf::RenderWindow &window, float direction) {
	pos_x += direction * walk_speed;
	animation_index = (animation_index + 1) % std::size(jeff_walking_left);
}

void Jeff::j_attack(sf::RenderWindow &window) {
	animation_index = (animation_index + 1) % std::size(jeff_shooting);
}

void Jeff::draw(sf::RenderWindow &window, sf::View &view, int &switch_control, bool &j_attack) {
	switch (switch_control) {
	case 1: {
		sf::Sprite sprite { jeff_standing_texture };
		sprite.setPosition(sf::Vector2f{ pos_x, pos_y });
		window.draw(sprite);

		ePos_x = x_finger_position_standing_right(sprite);
		ePos_y = y_finger_position_standing_right(sprite);

		break;
	}
	case 2: {
		sf::Sprite sprite { jeff_standing_left_texture };
		sprite.setPosition(sf::Vector2f{ pos_x, pos_y });
		window.draw(sprite);

		ePos_x = x_finger_position_standing_left(sprite);
		ePos_y = y_finger_position_standing_left(sprite);

		break;
	}
	case 3: {
		sf::Sprite sprite { jeff_walking_left_textures[animation_index] };
		sprite.setPosition(sf::Vector2f{ pos_x, pos_y });
		window.draw(sprite);

		ePos_x = x_finger_position_wl(sprite);
		ePos_y = y_finger_position_wl(sprite);

		switch_control = 2;
		break;
	}
	case 4: {
		sf::Sprite sprite { jeff_walking_textures[animation_index] };
		sprite.setPosition(sf::Vector2f{ pos_x, pos_y });
		window.draw(sprite);

		ePos_x = x_finger_position_wr(sprite);
		ePos_y = y_finger_position_wr(sprite);

		switch_control = 1;
		break;
	}
	}
}

void Jeff::draw_debug(sf::RenderWindow &window) {
	auto bounds = global_bounds();
	sf::RectangleShape shape { bounds.size };
	shape.setPosition(bounds.position);
	shape.setOutlineThickness(4.0f);
	shape.setOutlineColor(sf::Color::Magenta);
	shape.setFillColor(sf::Color::Transparent);
	window.draw(shape);
}

sf::FloatRect Jeff::global_bounds() {
	return { { pos_x, pos_y }, hitbox_size };
}

void Jeff::update_y() {
	velocity_y += gravity;
	pos_y += velocity_y;
}
