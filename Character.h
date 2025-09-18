#pragma once
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Character {
public:
	virtual int generate(const std::filesystem::path& asset_dir) = 0;
	virtual void walk_right(sf::Time dt) = 0;
	virtual void walk_left(sf::Time dt) = 0;
	virtual void draw(sf::RenderWindow &window, sf::View &view, int &switch_statement, bool &j_attack) = 0;
	virtual void j_attack(sf::RenderWindow &window) = 0;
};
