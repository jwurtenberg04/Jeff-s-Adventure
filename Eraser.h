#pragma once
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class Eraser {
public:
	Eraser(sf::Vector2f position, sf::Vector2f velocity);
	void draw(sf::RenderWindow &window);
	void move(sf::Time dt);
	sf::FloatRect getRect();
	void draw_debug(sf::RenderWindow &window);
	static bool load_texture(const std::filesystem::path& asset_dir);

private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	static sf::Texture texture;
};
