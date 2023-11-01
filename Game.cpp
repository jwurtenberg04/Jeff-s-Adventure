#include "Game.h"
#include "platform.h"

int Game::generate() {
	return background_level_one.loadFromFile(level_one) ? EXIT_SUCCESS : EXIT_FAILURE;
}

#ifdef JEFFS_ADVENTURE_IS_DANIEL
bool Game::collide_sprite(sf::Sprite a, sf::Sprite b) {
	return a.getGlobalBounds().findIntersection(b.getGlobalBounds()).has_value();
}

bool Game::collide_shape(sf::Sprite a, sf::ConvexShape b) {
	return a.getGlobalBounds().findIntersection(b.getGlobalBounds()).has_value();
}

bool Game::collide_rect_and_shape(sf::FloatRect rect, sf::ConvexShape shape) {
	return rect.findIntersection(shape.getGlobalBounds()).has_value();
}
#else
bool Game::collide_sprite(sf::Sprite a, sf::Sprite b) {
	return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

bool Game::collide_shape(sf::Sprite a, sf::ConvexShape b) {
	return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

bool Game::collide_rect_and_shape(sf::FloatRect rect, sf::ConvexShape shape) {
	return rect.intersects(shape.getGlobalBounds());
}
#endif

void Game::draw(sf::RenderWindow &window) {
	sprite.setTexture(background_level_one);
	window.draw(sprite);

	sf::Color blue{ 0, 0, 255 };
	Platform pl1(520, 520, 960, 520);
	Platform pl2(3260, 520, 3650, 520);
	Platform pl3(7100, 520, 7560, 520);
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
	// wall_1.setFillColor(blue);
	// window.draw(wall_1);

	wall_2.setPointCount(4);
	wall_2.setPoint(0, sf::Vector2f(10000, 420));
	wall_2.setPoint(1, sf::Vector2f(10000, 0));
	wall_2.setPoint(2, sf::Vector2f(10040, 0));
	wall_2.setPoint(3, sf::Vector2f(10040, 420));
	// wall_2.setFillColor(blue);
	// window.draw(wall_2);
}
