#include "Jeff.h"

int Jeff::generate() {
	if (!jeff_standing_texture.loadFromFile(jeff_standing)) return EXIT_FAILURE;
	if (!jeff_standing_left_texture.loadFromFile(jeff_standing_left)) return EXIT_FAILURE;
	for (int i = 0; i < std::size(jeff_walking); i++) {
		if (!jeff_walking_textures[i].loadFromFile(jeff_walking[i]))
			return EXIT_FAILURE;
	}
	for (int i = 0; i < std::size(jeff_walking_left); i++) {
		if (!jeff_walking_left_textures[i].loadFromFile(jeff_walking_left[i]))
			return EXIT_FAILURE;
	}
	for (int i = 0; i < std::size(jeff_shooting); i++) {
		if (!jeff_shooting_textures[i].loadFromFile(jeff_shooting[i]))
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

void Jeff::walk_right(sf::RenderWindow &window, float direction) {
	pos_x += direction * walk_speed;

	// Loop through the animation when walking.
	// The % operator wraps animation_index around back to 0 once it reaches the limit.
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
	case 1:
		sprite.setPosition(sf::Vector2f{ pos_x, pos_y });
		sprite.setTexture(jeff_standing_texture);
		window.draw(sprite);

		ePos_x = x_finger_position_standing_right(sprite);
		ePos_y = y_finger_position_standing_right(sprite);

		break;
	case 2:
		sprite.setPosition(sf::Vector2f{ pos_x, pos_y });
		sprite.setTexture(jeff_standing_left_texture);
		window.draw(sprite);

		ePos_x = x_finger_position_standing_left(sprite);
		ePos_y = y_finger_position_standing_left(sprite);

		break;
	case 3:
		sprite.setPosition(sf::Vector2f{ pos_x, pos_y });
		sprite.setTexture(jeff_walking_left_textures[animation_index]);
		window.draw(sprite);

		ePos_x = x_finger_position_wl(sprite);
		ePos_y = y_finger_position_wl(sprite);

		switch_control = 2;
		break;
	case 4:
		sprite.setPosition(sf::Vector2f{ pos_x, pos_y });
		sprite.setTexture(jeff_walking_textures[animation_index]);
		window.draw(sprite);

		ePos_x = x_finger_position_wr(sprite);
		ePos_y = y_finger_position_wr(sprite);

		switch_control = 1;
		break;
	}
}

sf::FloatRect Jeff::global_bounds() {
	auto global_bounds = sprite.getGlobalBounds();
	global_bounds.left = pos_x;
	global_bounds.top = pos_y;
	return global_bounds;
}

void Jeff::update_y() {
	pos_y += velocity_y;
}
