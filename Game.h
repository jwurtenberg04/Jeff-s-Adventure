#pragma once
#include <filesystem>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Jeff.h"
#include "Platform.h"

class Game
{
public:
	int generate(const std::filesystem::path& asset_dir);
	void draw(sf::RenderWindow &window);
	void draw_debug(sf::RenderWindow &window);
	void init_level();
	void collide_jeff(Jeff& jeff);

private:
	static constexpr const char* level_one = "jeff's-adventure-background-1.png";
	sf::Texture background_level_one;
	std::vector<Platform> platforms;
};
