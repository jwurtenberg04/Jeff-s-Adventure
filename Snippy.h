#pragma once
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Snippy
{
public:
	int generate(const std::filesystem::path& asset_dir);
	void walk_right(sf::Time dt);
	void walk_left(sf::Time dt);
	void draw(sf::RenderWindow &window, sf::View &view, int switch_control);
	void spawn(int xPos, int yPos);
	sf::FloatRect global_bounds() const;
	float pos_x = 600.0f;
	float pos_y = 490.0f;
	// `walk_speed` is in viewport units per second.
	static constexpr float walk_speed = 150.0f;
	static constexpr sf::Vector2f hitbox_size { 300.0f, 237.0f };

private:
	sf::Clock animation_clock;
	long current_frame(long frame_count) const;

	static constexpr const char* snippyRight[] = {
		"Snippy/Snippy-Right00.png","Snippy/Snippy-Right00.png", "Snippy/Snippy-Right00.png", "Snippy/Snippy-Right01.png" , "Snippy/Snippy-Right02.png", "Snippy/Snippy-Right03.png",
		"Snippy/Snippy-Right04.png", "Snippy/Snippy-Right04.png","Snippy/Snippy-Right04.png","Snippy/Snippy-Right05.png", "Snippy/Snippy-Right06.png", "Snippy/Snippy-Right07.png",
		"Snippy/Snippy-Right08.png","Snippy/Snippy-Right08.png","Snippy/Snippy-Right08.png", "Snippy/Snippy-Right09.png", "Snippy/Snippy-Right10.png", "Snippy/Snippy-Right11.png",
		"Snippy/Snippy-Right12.png","Snippy/Snippy-Right12.png","Snippy/Snippy-Right12.png", "Snippy/Snippy-Right13.png", "Snippy/Snippy-Right14.png", "Snippy/Snippy-Right15.png",
		"Snippy/Snippy-Right16.png", "Snippy/Snippy-Right16.png","Snippy/Snippy-Right16.png","Snippy/Snippy-Right17.png", "Snippy/Snippy-Right18.png", "Snippy/Snippy-Right19.png",
		"Snippy/Snippy-Right20.png","Snippy/Snippy-Right20.png","Snippy/Snippy-Right20.png", "Snippy/Snippy-Right21.png", "Snippy/Snippy-Right22.png"
	};
	static constexpr const char* snippyLeft[] = {
		"Snippy/Snippy-Left00.png","Snippy/Snippy-Left00.png","Snippy/Snippy-Left00.png", "Snippy/Snippy-Left01.png" , "Snippy/Snippy-Left02.png", "Snippy/Snippy-Left03.png",
		"Snippy/Snippy-Left04.png","Snippy/Snippy-Left04.png","Snippy/Snippy-Left04.png", "Snippy/Snippy-Left05.png", "Snippy/Snippy-Left06.png", "Snippy/Snippy-Left07.png",
		"Snippy/Snippy-Left08.png","Snippy/Snippy-Left08.png","Snippy/Snippy-Left08.png", "Snippy/Snippy-Left09.png", "Snippy/Snippy-Left10.png", "Snippy/Snippy-Left11.png",
		"Snippy/Snippy-Left12.png","Snippy/Snippy-Left12.png","Snippy/Snippy-Left12.png", "Snippy/Snippy-Left13.png", "Snippy/Snippy-Left14.png", "Snippy/Snippy-Left15.png",
		"Snippy/Snippy-Left16.png","Snippy/Snippy-Left16.png","Snippy/Snippy-Left16.png", "Snippy/Snippy-Left17.png", "Snippy/Snippy-Left18.png", "Snippy/Snippy-Left19.png",
	};
	sf::Texture snippyIdleRight;
	sf::Texture snippyRightTextures[std::size(snippyRight)];
	sf::Texture snippyLeftTextures[std::size(snippyLeft)];
};

