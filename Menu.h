#pragma once

#include <SFML/Graphics.hpp>

class Menu {
public:
	int load();
	int characterSelect(sf::RenderWindow &window);
	void mouse(sf::RenderWindow &window);
private:
	sf::Texture tMouse;
	sf::Texture tScreen;
	sf::Texture tPlayer1;
	sf::Texture tPlayer2;
	sf::Sprite sMouse;
	sf::Sprite sScreen;
	sf::Sprite sPlayer1;
	sf::Sprite sPlayer2;
};
