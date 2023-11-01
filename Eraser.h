#pragma once
#include <SFML/Graphics.hpp>

class Eraser {
public:
	Eraser(sf::Vector2f position, sf::Vector2f velocity);
	void draw(sf::RenderWindow &window);
	void move();
	static bool load_texture();
private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Sprite sprite{};
	static sf::Texture texture;
};
