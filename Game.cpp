#include "Game.h"
#include "Platform.h"

int Game::generate(const std::filesystem::path& asset_dir) {
	if (!background_level_one.loadFromFile((asset_dir / level_one).string()))
		return EXIT_FAILURE;
	// Give the background a pixelated look.
	background_level_one.setSmooth(false);
	return EXIT_SUCCESS;
}

void Game::draw(sf::RenderWindow &window) {
	sf::Sprite sprite { background_level_one };
	window.draw(sprite);
}

void Game::draw_debug(sf::RenderWindow &window) const {
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
			// Move Jeff to the left edge of the wall.
			jeff.pos_x = platform_bounds.position.x - jeff_bounds.size.x;
			break;

		case Direction::right:
			// Move Jeff to the right edge of the wall.
			jeff.pos_x = platform_bounds.position.x + platform_bounds.size.x;
			break;

		case Direction::top: {
			// Move Jeff to the top of the floor.
			jeff.pos_y = platform_bounds.position.y - jeff_bounds.size.y;
			// If the player is pressing the space key, then Jeff should jump.
			// Else, prevent Jeff from falling into the floor.
			bool pressing_space = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space);
			jeff.velocity_y = pressing_space ? -jeff.jeff_jump_strength : 0.0f;
			break;
		}

		case Direction::bottom:
			jeff.pos_y = platform_bounds.position.y + platform_bounds.size.y;
			jeff.velocity_y = 0.0f;
			break;
		}
	}
}
