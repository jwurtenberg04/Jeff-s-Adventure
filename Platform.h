#pragma once
#include <SFML/Graphics.hpp>
class Platform
{
public:
	Platform(int x1, int y1, int x2, int y2);
	Platform(int x1, int y1, int x2, int y2, int x3, int y3);
	Platform(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
	Platform(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5);
	Platform(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int x5, int y5, int x6, int y6);
	bool collide(sf::Sprite a, sf::ConvexShape b);
	sf::ConvexShape platform;
};

