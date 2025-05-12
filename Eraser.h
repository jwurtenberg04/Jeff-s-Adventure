#pragma once
#include <filesystem>
#include <SFML/Graphics.hpp>

class Eraser {
public:
	Eraser(sf::Vector2f position, sf::Vector2f velocity);
	void draw(sf::RenderWindow &window);
	void move();
	static bool load_texture(std::filesystem::path asset_dir);
private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	static sf::Texture texture;
};
