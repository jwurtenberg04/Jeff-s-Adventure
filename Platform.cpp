#include "Platform.h"

Platform::Platform(int x1, int y1, int x2, int y2) {
	platform.setPointCount(2);
	platform.setPoint(1, sf::Vector2f(x1, y1));
	platform.setPoint(2, sf::Vector2f(x2, y2));
}
Platform::Platform(int x1, int y1, int x2, int y2, int x3, int y3) {
	platform.setPointCount(3);
	platform.setPoint(1, sf::Vector2f(x1, y1));
	platform.setPoint(2, sf::Vector2f(x2, y2));
	platform.setPoint(3, sf::Vector2f(x3, y3));
}
Platform::Platform(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	platform.setPointCount(4);
	platform.setPoint(1, sf::Vector2f(x1, y1));
	platform.setPoint(2, sf::Vector2f(x2, y2));
	platform.setPoint(3, sf::Vector2f(x3, y3));
	platform.setPoint(4, sf::Vector2f(x4, y4));
}
Platform::Platform(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5) {
	platform.setPointCount(5);
	platform.setPoint(1, sf::Vector2f(x1, y1));
	platform.setPoint(2, sf::Vector2f(x2, y2));
	platform.setPoint(3, sf::Vector2f(x3, y3));
	platform.setPoint(4, sf::Vector2f(x4, y4));
	platform.setPoint(5, sf::Vector2f(x5, y5));
}
Platform::Platform(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5, int x6, int y6) {
	platform.setPointCount(6);
	platform.setPoint(1, sf::Vector2f(x1, y1));
	platform.setPoint(2, sf::Vector2f(x2, y2));
	platform.setPoint(3, sf::Vector2f(x3, y3));
	platform.setPoint(4, sf::Vector2f(x4, y4));
	platform.setPoint(5, sf::Vector2f(x5, y5));
	platform.setPoint(6, sf::Vector2f(x6, y6));
}

bool Platform::collide(sf::Sprite a, sf::ConvexShape b) {
	return a.getGlobalBounds().intersects(b.getGlobalBounds());
}