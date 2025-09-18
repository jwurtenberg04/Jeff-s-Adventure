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
#include "Eraser.h"
#include "Snippy.h"

namespace filesystem = std::filesystem;

// To find the asset directory, we begin at the directory containing the
// executable and move up until we find `test_asset_path`.
static const char* test_asset_path = "Snippy-1.png";

// Return the absolute path to the directory containing all of the assets.
// Return an empty path if the asset directory could not be found.
static filesystem::path find_asset_dir();

static const int view_height = 800;

static void create_window(sf::Window& window, bool in_fullscreen = false) {
	// Default settings for Jeff's Adventure:
	sf::VideoMode video_mode { { 1'000, view_height } };
	sf::State state = sf::State::Windowed;
	if (in_fullscreen) {
		auto fullscreen_modes = sf::VideoMode::getFullscreenModes();
		if (fullscreen_modes.empty()) {
			// Fullscreen is not supported.
			// Fallback to default settings.
		} else {
			// Pick the best video mode (always at index 0).
			video_mode = fullscreen_modes.at(0);
			state = sf::State::Fullscreen;
		}
	}
	window.create(video_mode, "Jeff's Adventure!", state);
	window.setVerticalSyncEnabled(true);
}

int main() {
	auto asset_dir = find_asset_dir();
	if (asset_dir.empty()) {
		std::cerr << "Could not find the asset directory.\n";
		return 1;
	}
	std::cout << "Asset directory: " << asset_dir << '\n';

	auto new_eraser = std::chrono::high_resolution_clock::now();
	auto last_eraser = std::chrono::high_resolution_clock::now();
	int switch_control = 1;
	bool j_attack;
	bool in_fullscreen = false;
	bool f_key_previously_pressed = false;
	sf::RenderWindow window;
	create_window(window);
	sf::View view;
	Snippy snippy;
	Jeff jeff;
	Game game;
	int snippy_switch_control = 2;
	bool snippy_alive = true;

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
	game.init_level();
	sf::Clock clock;
	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			} else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
				if (key->code == sf::Keyboard::Key::F) {
					bool control = !key->alt && key->control && !key->shift && !key->system;
					// Ignore repeated key presses.
					if (!f_key_previously_pressed && control) {
						in_fullscreen = !in_fullscreen;
						create_window(window, in_fullscreen);
					}
					f_key_previously_pressed = true;
				}
			} else if (const auto* key = event->getIf<sf::Event::KeyReleased>()) {
				if (key->code == sf::Keyboard::Key::F)
					f_key_previously_pressed = false;
			}
		}

		// Limit `dt`. Falling behind is better than simulating, for instance,
		// 500 ms of time in one time step, which may lead to tunneling.
		const sf::Time dt = std::min(sf::milliseconds(50), clock.restart());

		// If the window is not focused, we intentionally let the game fall
		// behind. Unfocusing the window effectively pauses the game.
		if (!window.hasFocus()) {
			window.display();
			continue;
		}

		j_attack = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			window.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) {
			jeff.walk_left(dt);
			switch_control = 3;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) {
			jeff.walk_right(dt);
			switch_control = 4;
		}

		//haha bang bang shoot
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::J)) {
			new_eraser = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(new_eraser - last_eraser);

			float direction = switch_control == 1 || switch_control == 4 ? 1.0f : -1.0f;
			float horizontal_velocity = direction * 600.0f;
			if (duration.count() > 500) {
				j_attack = true;
				erasers.push_back(Eraser{ {jeff.ePos_x, jeff.ePos_y}, sf::Vector2f{horizontal_velocity, 0} });
				last_eraser = std::chrono::high_resolution_clock::now();
			}
		}

		// Update Jeff's position before handling collisions and rendering.
		jeff.update_y(dt);

		if (snippy_alive && jeff.global_bounds().findIntersection(snippy.global_bounds())) {
			jeff.pos_x = 150.0f;
		}

		game.collide_jeff(jeff);

		sf::Color background_color{ 120, 75, 45 };
		window.clear(background_color);
		const auto window_size = sf::Vector2f { window.getSize() };
		const float width = window_size.x / window_size.y * view_height;
		view.setSize(sf::Vector2f { width, view_height });
		view.setCenter(sf::Vector2f { jeff.pos_x + width / 2.0f, 395.0f });
		window.setView(view);
		game.draw(window);
		game.draw_debug(window);
		for (auto &eraser : erasers) {
			eraser.move(dt);
			eraser.draw(window);
		}

		if (jeff.pos_x < snippy.pos_x) {
			snippy.walk_left(dt);
			snippy_switch_control = 2;
		} else {
			snippy.walk_right(dt);
			snippy_switch_control = 1;
		}

		if (snippy_alive) {
			snippy.draw(window, view, snippy_switch_control);
		}

		jeff.draw(window, view, switch_control, j_attack);
		jeff.draw_debug(window);
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
