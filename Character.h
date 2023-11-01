#pragma once
#include <SFML/Graphics.hpp>

class Character {
public:
	virtual int generate() = 0;
	virtual void walk_right(sf::RenderWindow &window, float direction) = 0;
	virtual void walk_left(sf::RenderWindow &window, float direction) = 0;
	virtual void draw(sf::RenderWindow &window, sf::View &view, int &switch_statement, bool &j_attack) = 0;
	virtual void j_attack(sf::RenderWindow &window) = 0;
};
