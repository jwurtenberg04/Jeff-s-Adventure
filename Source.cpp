#include <iostream>
#include <chrono>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Jeff.h"
#include "Menu.h"
#include "Character.h"
#include "Eraser.h"
#include "Snippy.h"

int main() {
	auto asset_dir = std::filesystem::current_path();
	std::cout << "Asset directory: " << asset_dir << '\n';

	constexpr float gravity = 0.7f;
	auto new_eraser = std::chrono::high_resolution_clock::now();
	auto last_eraser = std::chrono::high_resolution_clock::now();
	int switch_control = 1;
	bool j_attack;
	sf::RenderWindow window;
	window.create(sf::VideoMode(1000, 800), "Jeff's Adventure!");
	window.setFramerateLimit(60);
	sf::View view;
	view.setSize(sf::Vector2f(1500, 800));
	Snippy snippy;
	Jeff jeff;
	Game game;

	// Load all of the images and convert them to textures once.
	if (jeff.generate(asset_dir) == EXIT_FAILURE) {
		std::cerr << "Could not load Jeff textures.\n";
		return EXIT_FAILURE;
	}
	if (game.generate(asset_dir) == EXIT_FAILURE) {
		std::cerr << "Could not load global game textures.\n";
		return EXIT_FAILURE;
	}

	std::vector<Eraser> erasers{};
	if (!Eraser::load_texture(asset_dir)) {
		std::cerr << "Could not load eraser texture.\n";
		return EXIT_FAILURE;
	}
	if (snippy.generate(asset_dir) == EXIT_FAILURE) {
		std::cerr << "Could not load Snippy textures.\n";
		return EXIT_FAILURE;
	}
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		j_attack = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			jeff.walk_left(window, -1.0f);
			switch_control = 3;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			jeff.walk_right(window, 1.0f);
			switch_control = 4;
		}

		//haha bang bang shoot
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
			new_eraser = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(new_eraser - last_eraser);

			float horizontal_velocity = switch_control == 1 || switch_control == 4 ? 10 : -10;
			if (duration.count() > 500) {
				j_attack = true;
				erasers.push_back(Eraser{ {jeff.ePos_x, jeff.ePos_y}, sf::Vector2f{horizontal_velocity, 0} });
				last_eraser = std::chrono::high_resolution_clock::now();
			}
		}

		// Update Jeff's position before handling collisions and rendering.
		jeff.update_y();

		bool collide_floor = game.collide_rect_and_shape(jeff.global_bounds(), game.floor);
		if (collide_floor) {
			// Move Jeff to the top of the floor.
			jeff.pos_y = game.floor.getGlobalBounds().top - jeff.global_bounds().height + 1;
			// If the player is pressing the space key, then Jeff should jump.
			// Else, prevent Jeff from falling into the floor.
			bool pressing_space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
			jeff.velocity_y = pressing_space ? -jeff.jeff_jump_strength : 0.0f;
		} else {
			jeff.velocity_y += gravity;
		}

		if (game.collide_rect_and_shape(jeff.global_bounds(), game.wall_1)) {
			const auto bounds = game.wall_1.getGlobalBounds();
			// Move Jeff to the right edge of the wall.
			jeff.pos_x = bounds.left + bounds.width;
		}

		if (game.collide_rect_and_shape(jeff.global_bounds(), game.wall_2)) {
			const auto bounds = game.wall_2.getGlobalBounds();
			// Move Jeff to the left edge of the wall.
			jeff.pos_x = bounds.left - jeff.global_bounds().width;
		}

		sf::Color background_color{ 120, 75, 45 };
		window.clear(background_color);
		view.setCenter(sf::Vector2f(jeff.pos_x + 500, 395));
		window.setView(view);
		game.draw(window);
		for (auto &eraser : erasers) {
			eraser.move();
			eraser.draw(window);
		}
		jeff.draw(window, view, switch_control, j_attack);
		window.display();
	}

	return EXIT_SUCCESS;
}
