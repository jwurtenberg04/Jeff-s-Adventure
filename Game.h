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
	void draw(sf::RenderWindow &window);
	void init_level();
	static bool collide_sprite(sf::Sprite a, sf::Sprite b);
	void collide_jeff(Jeff& jeff);

private:
	static constexpr const char* level_one = "jeff's-adventure-background-1.png";
	sf::Texture background_level_one;
	sf::Sprite sprite;
	std::vector<Platform> platforms;
};
