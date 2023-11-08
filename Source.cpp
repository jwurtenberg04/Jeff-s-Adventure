#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cassert>
#include <iomanip>
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

namespace filesystem = std::filesystem;

// To find the asset directory, we begin at the directory containing the
// executable and move up until we find `test_asset_path`.
static const char* test_asset_path = "Snippy-1.png";

// Return the absolute path to the directory containing all of the assets.
// Return an empty path if the asset directory could not be found.
static filesystem::path find_asset_dir();

int main() {
	auto asset_dir = find_asset_dir();
	if (asset_dir.empty()) {
		std::cerr << "Could not find the asset directory.\n";
		return 1;
	}
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

		if (snippy_alive && game.collide_sprite(jeff.sprite, snippy.sprite)) {
			jeff.pos_x = 250.0f;
		}

		if (game.collide_rect_and_shape(jeff.global_bounds(), game.floor);) {
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

		if (jeff.pos_x < snippy.pos_x) {
			snippy.walk_left(window);
			snippy_switch_control = 2;
		} else {
			snippy.walk_right(window);
			snippy_switch_control = 1;
		}

		if (snippy_alive) {
			snippy.draw(window, view, snippy_switch_control);
		}

		jeff.draw(window, view, switch_control, j_attack);
		window.display();
	}

	return EXIT_SUCCESS;
}

// Return the absolute path to the main executable file.
static filesystem::path get_executable_path() {
	// Allocate a reasonably-sized buffer.
	std::vector<wchar_t> buffer(MAX_PATH);
	while (true) {
		// For `GetModuleFileNameW`, `NULL` represents the current process.
		const DWORD length_excluding_null = GetModuleFileNameW(NULL, buffer.data(), buffer.size());
		const DWORD error = GetLastError();
		if (length_excluding_null == 0) {
			std::cerr << "Cannot get path to main executable file: Win32 error ";
			std::cerr << std::setfill('0') << std::setw(8) << std::hex << std::uppercase;
			std::cerr << error << '\n';
			std::exit(1);
		}
		// Check if the buffer was big enough. If the length (excluding the null
		// byte) is equal to the buffer's size, the path was truncated.
		if (error == ERROR_INSUFFICIENT_BUFFER || length_excluding_null == buffer.size()) {
			buffer.resize(buffer.size() * 2);
			continue;
		}
		// The buffer was big enough.
		// The length must not exceed the buffer's size.
		assert(length_excluding_null < buffer.size());
		// The buffer must be null terminated.
		assert(buffer.at(length_excluding_null) == '\0');
		break;
	}
	filesystem::path path { &buffer.at(0) };
	assert(path.is_absolute());
	return path;
}

static filesystem::path find_asset_dir() {
	// Get the path to the directory containing the executable.
	auto current_dir = get_executable_path().parent_path();
	while (!current_dir.empty()) {
		// Check if the test asset is in `current_dir`.
		if (filesystem::exists(current_dir / test_asset_path))
			return current_dir;
		// Additionally, check any "SFML" subdirectories.
		// This ensures that the assets can be found on my computer and Josh's computer.
		if (filesystem::exists(current_dir / "SFML" / test_asset_path))
			return current_dir / "SFML";
		// The test asset isn't under `current_dir`, so move up.
		if (current_dir.has_parent_path() && current_dir.has_relative_path()) {
			current_dir = current_dir.parent_path();
		} else {
			// We can't move up anymore, meaning we couldn't find the assets.
			// Return an empty path to indicate failure.
			return {};
		}
	}
	return {};
}
