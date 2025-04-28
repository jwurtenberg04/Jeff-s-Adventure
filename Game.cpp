#include "Game.h"

int Game::generate(std::filesystem::path asset_dir) {
	if (!background_level_one.loadFromFile((asset_dir / level_one).string()))
		return EXIT_FAILURE;
	// We want the background to have a pixelated look.
	background_level_one.setSmooth(false);
	return EXIT_SUCCESS;
}

bool Game::collide_sprite(sf::Sprite a, sf::Sprite b) {
	return a.getGlobalBounds().findIntersection(b.getGlobalBounds()).has_value();
}

void Game::draw(sf::RenderWindow &window) {
	sprite.setTexture(background_level_one);
	window.draw(sprite);
}

void Game::draw_debug(sf::RenderWindow &window) {
	for (const auto& platform : platforms)
		platform.draw(window);
}

void Game::init_level() {
	platforms.push_back({ { 0, 695 }, { 10'000, 25 }, sf::Color::Red }); // Floor
	platforms.push_back({ { -40, 0 }, { 40, 720 }, sf::Color::Green }); // Wall 1
	platforms.push_back({ { 10'000, 0 }, { 40, 720 }, sf::Color::Blue }); // Wall 2
	platforms.push_back({ { 500, 500 }, { 440, 25 }, sf::Color::Cyan });
}

void Game::collide_jeff(Jeff& jeff) {
	for (const auto& platform : platforms) {
		auto platform_bounds = platform.global_bounds();
		auto jeff_bounds = jeff.global_bounds();
		auto maybe_collision = platform.collide(jeff_bounds);
		// Ignore platforms that aren't colliding with Jeff.
		if (!maybe_collision)
			continue;
		Collision collision = maybe_collision.value();
		switch (collision.from) {
		case Direction::left:
			// Move Jeff before the left edge of the wall.
			jeff.pos_x = platform_bounds.left - jeff_bounds.width;
			break;

		case Direction::right:
			// Move Jeff to the right edge of the wall.
			jeff.pos_x = platform_bounds.left + platform_bounds.width;
			break;

		case Direction::top: {
			// Move Jeff before the top of the floor.
			jeff.pos_y = platform_bounds.top - jeff_bounds.height;
			// If the player is pressing the space key, then Jeff should jump.
			// Otherwise Jeff is on the floor and shouldn't fall into it.
			bool pressing_space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
			jeff.velocity_y = pressing_space ? -jeff.jeff_jump_strength : 0.0f;
			break;
		}

		case Direction::bottom:
			jeff.pos_y = platform_bounds.top + platform_bounds.height;
			jeff.velocity_y = 0.0f;
			break;
		}
	}
}
