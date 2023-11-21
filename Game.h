#pragma once
#include <filesystem>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Jeff.h"
#include "Platform.h"

class Game
{
public:
	int generate(std::filesystem::path asset_dir);
	static bool collide_sprite(sf::Sprite a, sf::Sprite b);
	void draw(sf::RenderWindow &window);
	void draw_debug(sf::RenderWindow &window);
	void init_level();
	void collide_jeff(Jeff& jeff);

private:
	static constexpr const char* level_one = "jeff's-adventure-background-1.png";
	std::vector<Platform> platforms;
	sf::Texture background_level_one;
	sf::Sprite sprite;
};
