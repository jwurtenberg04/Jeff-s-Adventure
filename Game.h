#pragma once
#include <filesystem>
#include <SFML/Graphics.hpp>

class Game
{
public:
	int generate(std::filesystem::path asset_dir);
	void draw(sf::RenderWindow &window);
	static bool collide_sprite(sf::Sprite a, sf::Sprite b);
	bool collide_rect_and_shape(sf::FloatRect rect, sf::ConvexShape shape);
	sf::ConvexShape floor;
	sf::ConvexShape wall_1;
	sf::ConvexShape wall_2;

private:
	static constexpr const char* level_one = "jeff's-adventure-background-1.png";
	sf::Texture background_level_one;
	sf::Sprite sprite;
};
