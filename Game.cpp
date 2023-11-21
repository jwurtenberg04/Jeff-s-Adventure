#include "Game.h"

int Game::generate(std::filesystem::path asset_dir) {
	if (!background_level_one.loadFromFile((asset_dir / level_one).string()))
		return EXIT_FAILURE;
	// We want the background to have a pixelated look.
	background_level_one.setSmooth(false);
	return EXIT_SUCCESS;
}

bool Game::collide_sprite(sf::Sprite a, sf::Sprite b) {
	return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

bool Game::collide_rect_and_shape(sf::FloatRect rect, sf::ConvexShape shape) {
	return rect.intersects(shape.getGlobalBounds());
}

void Game::draw(sf::RenderWindow &window) {
	sprite.setTexture(background_level_one);
	window.draw(sprite);

	sf::Color blue{ 0, 0, 255 };
	floor.setPointCount(4);
	floor.setPoint(0, sf::Vector2f(0, 695));
	floor.setPoint(1, sf::Vector2f(0, 720));
	floor.setPoint(2, sf::Vector2f(10000, 720));
	floor.setPoint(3, sf::Vector2f(10000, 695));
	// window.draw(floor);

	wall_1.setPointCount(4);
	wall_1.setPoint(0, sf::Vector2f(245, 420));
	wall_1.setPoint(1, sf::Vector2f(245, 0));
	wall_1.setPoint(2, sf::Vector2f(-40, 0));
	wall_1.setPoint(3, sf::Vector2f(-40, 420));
	//wall_1.setFillColor(blue);
	//window.draw(wall_1);

	wall_2.setPointCount(4);
	wall_2.setPoint(0, sf::Vector2f(10000, 420));
	wall_2.setPoint(1, sf::Vector2f(10000, 0));
	wall_2.setPoint(2, sf::Vector2f(10040, 0));
	wall_2.setPoint(3, sf::Vector2f(10040, 420));
	//wall_2.setFillColor(blue);
	//window.draw(wall_2);
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
