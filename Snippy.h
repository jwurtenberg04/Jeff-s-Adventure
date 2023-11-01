#pragma once
#include <SFML/Graphics.hpp>

class Snippy
{
public:
	int generate();
	void walk_right(sf::RenderWindow &window, float direction);
	void walk_left(sf::RenderWindow &window, float direction);
	void draw(sf::RenderWindow &window, sf::View &view, int &switch_control);
	void spawn(int xPos, int yPos);
	sf::FloatRect global_bounds();
	void update_y();
	float pos_x = 250.0f;
	float pos_y = 395.0f;
	float velocity_y = 0.0f;
	static constexpr float walk_speed = 4.5f;
	float snippy_jump_strength = 17.0f;
	sf::Sprite sprite;
private:
	sf::Texture snippyIdleRight;
};

