#include "Menu.h"
#include <iostream>

int Menu::load() {
	if (!tScreen.loadFromFile("characterSelect.png"))
		return EXIT_FAILURE;
	sScreen.setTexture(tScreen);

	if (!tMouse.loadFromFile("mouseCursor.png"))
		return EXIT_FAILURE;
	sMouse.setTexture(tMouse);
	sMouse.setOrigin(sf::Vector2f(11.0f, 6.0f));
	return EXIT_SUCCESS;
}

int Menu::characterSelect(sf::RenderWindow &window) {
	window.draw(sScreen);
	return 1;
	// if ((sScreen.getPosition().x <= sf::Mouse::getPosition().x + 100) && (sScreen.getPosition().x >= sf::Mouse::getPosition().x - 100) && (sScreen.getPosition().y <= sf::Mouse::getPosition().y + 100) && (sScreen.getPosition().y >= sf::Mouse::getPosition().y - 100))
	// {
	// 	return 1;
	// }
}

void Menu::mouse(sf::RenderWindow &window) {
	sMouse.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
	window.draw(sMouse);
}
