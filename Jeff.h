#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Character.h"

class Jeff : public Character {
public:
	virtual int generate(const std::filesystem::path& asset_dir) override;
	void walk_right(sf::Time dt) override;
	void walk_left(sf::Time dt) override;
	void draw(sf::RenderWindow &window, sf::View &view, int &switch_control, bool &j_attack);
	void draw_debug(sf::RenderWindow &window) const;
	void j_attack(sf::RenderWindow &window);
	sf::FloatRect global_bounds() const;
	void update_y(sf::Time dt);
	float ePos_x;
	float ePos_y;
	float pos_x = 150.0f;
	float pos_y = 395.0f;
	float velocity_y = 0.0f;
	// `walk_speed` is in viewport units per second.
	static constexpr float walk_speed = 300.0f;
	// `gravity` is in viewport units per second squared.
	static constexpr float gravity = 2520.0f;
	// `jeff_jump_strength` is in viewport units per second.
	float jeff_jump_strength = 1020.0f;
	static constexpr sf::Vector2f hitbox_size { 300.0f, 300.0f };

private:
	sf::Vector2f finger_stand_right = { 100, 23 };
	sf::Vector2f finger_stand_left = { -100, 23 };
	sf::Vector2f finger_walk_right[47] = {
		{ 100, 23 }, { 100, 23 }, { 100, 23 }, { 100, 23 }, { 100, 23 },
		{ 100, 30 }, { 100, 30 }, { 100, 30 }, { 100, 30 }, { 100, 30 },
		{ 100, 37 }, { 100, 37 }, { 100, 37 }, { 100, 37 }, { 100, 37 },
		{ 100, 44 }, { 100, 44 }, { 100, 44 }, { 100, 44 }, { 100, 44 },
		{ 100, 31 }, { 100, 31 }, { 100, 31 }, { 100, 31 }, { 100, 31 },
		{ 100, 19 }, { 100, 19 }, { 100, 19 }, { 100, 19 }, { 100, 19 },
		{ 100, 16 }, { 100, 16 }, { 100, 16 }, { 100, 16 }, { 100, 16 },
		{ 100, 13 }, { 100, 13 }, { 100, 13 }, { 100, 13 }, { 100, 13 },
		{ 100, 10 }, { 100, 10 }, { 100, 10 }, { 100, 10 }, { 100, 10 },
		{ 100, 10 }, { 100, 10 }
	};
	sf::Vector2f finger_walk_left[45] = {
		{ -100, 23 }, { -100, 23 }, { -100, 23 }, { -100, 23 }, { -100, 23 },
		{ -100, 30 }, { -100, 30 }, { -100, 30 }, { -100, 30 }, { -100, 30 },
		{ -100, 37 }, { -100, 37 }, { -100, 37 }, { -100, 37 }, { -100, 37 },
		{ -100, 44 }, { -100, 44 }, { -100, 44 }, { -100, 44 }, { -100, 44 },
		{ -100, 31 }, { -100, 31 }, { -100, 31 }, { -100, 31 }, { -100, 31 },
		{ -100, 19 }, { -100, 19 }, { -100, 19 }, { -100, 19 }, { -100, 19 },
		{ -100, 16 }, { -100, 16 }, { -100, 16 }, { -100, 16 }, { -100, 16 },
		{ -100, 13 }, { -100, 13 }, { -100, 13 }, { -100, 13 }, { -100, 13 },
		{ -100, 10 }, { -100, 10 }, { -100, 10 }, { -100, 10 }, { -100, 10 }
	};

	//returns the x and y positions for jeff's finger when facing right
	auto x_finger_position_standing_right(sf::Sprite &sprite) const {
		return finger_stand_right.x * sprite.getScale().x + sprite.getPosition().x;
	}

	auto y_finger_position_standing_right(sf::Sprite &sprite) const {
		return finger_stand_right.y * sprite.getScale().y + sprite.getPosition().y;
	}

	//returns the x and y positions for jeff's finger when facing left
	auto x_finger_position_standing_left(sf::Sprite &sprite) const {
		return finger_stand_left.x * sprite.getScale().x + sprite.getPosition().x;
	}

	auto y_finger_position_standing_left(sf::Sprite &sprite) const {
		return finger_stand_left.y * sprite.getScale().y + sprite.getPosition().y;
	}

	//returns the x and y positions for jeff's finger when walking right
	auto x_finger_position_wr(sf::Sprite &sprite) {
		return finger_walk_right[animation_index].x * sprite.getScale().x + sprite.getPosition().x;
	}

	auto y_finger_position_wr(sf::Sprite &sprite) {
		return finger_walk_right[animation_index].y * sprite.getScale().y + sprite.getPosition().y;
	}

	//returns the x and y positions for jeff's finger when walking left
	auto x_finger_position_wl(sf::Sprite &sprite) {
		return finger_walk_left[animation_index].x * sprite.getScale().x + sprite.getPosition().x;
	}

	auto y_finger_position_wl(sf::Sprite &sprite) {
		return finger_walk_left[animation_index].y * sprite.getScale().y + sprite.getPosition().y;
	}

	int animation_index = 0;

	// It's not a big deal, but we know all of these strings at compile time, so we don't really
	// need a fully dynamic string like std::string.
	static constexpr const char* jeff_standing = "jeff-standing.png";
	static constexpr const char* jeff_standing_left = "jeff-standing-left.png";
	static constexpr const char* jeff_walking[] = {
		"jeff-walking/jeff-walking-1.png", "jeff-walking/jeff-walking-2.png", "jeff-walking/jeff-walking-3.png",
		"jeff-walking/jeff-walking-4.png", "jeff-walking/jeff-walking-5.png", "jeff-walking/jeff-walking-6.png",
		"jeff-walking/jeff-walking-7.png", "jeff-walking/jeff-walking-8.png", "jeff-walking/jeff-walking-9.png",
		"jeff-walking/jeff-walking-10.png", "jeff-walking/jeff-walking-11.png", "jeff-walking/jeff-walking-12.png",
		"jeff-walking/jeff-walking-13.png", "jeff-walking/jeff-walking-14.png", "jeff-walking/jeff-walking-15.png",
		"jeff-walking/jeff-walking-16.png", "jeff-walking/jeff-walking-17.png", "jeff-walking/jeff-walking-18.png",
		"jeff-walking/jeff-walking-19.png", "jeff-walking/jeff-walking-20.png", "jeff-walking/jeff-walking-21.png",
		"jeff-walking/jeff-walking-22.png", "jeff-walking/jeff-walking-23.png", "jeff-walking/jeff-walking-24.png",
		"jeff-walking/jeff-walking-25.png", "jeff-walking/jeff-walking-26.png", "jeff-walking/jeff-walking-27.png",
		"jeff-walking/jeff-walking-28.png", "jeff-walking/jeff-walking-29.png", "jeff-walking/jeff-walking-30.png",
		"jeff-walking/jeff-walking-31.png", "jeff-walking/jeff-walking-32.png", "jeff-walking/jeff-walking-33.png",
		"jeff-walking/jeff-walking-34.png", "jeff-walking/jeff-walking-35.png", "jeff-walking/jeff-walking-36.png",
		"jeff-walking/jeff-walking-37.png", "jeff-walking/jeff-walking-38.png", "jeff-walking/jeff-walking-39.png",
		"jeff-walking/jeff-walking-40.png", "jeff-walking/jeff-walking-41.png", "jeff-walking/jeff-walking-42.png",
		"jeff-walking/jeff-walking-43.png", "jeff-walking/jeff-walking-44.png", "jeff-walking/jeff-walking-45.png",
		"jeff-walking/jeff-walking-46.png", "jeff-walking/jeff-walking-47.png"
	};
	static constexpr const char* jeff_walking_left[] = {
		"jeff-walking/jeff-walking-left-00.png", "jeff-walking/jeff-walking-left-01.png", "jeff-walking/jeff-walking-left-02.png",
		"jeff-walking/jeff-walking-left-03.png", "jeff-walking/jeff-walking-left-04.png", "jeff-walking/jeff-walking-left-05.png",
		"jeff-walking/jeff-walking-left-06.png", "jeff-walking/jeff-walking-left-07.png", "jeff-walking/jeff-walking-left-08.png",
		"jeff-walking/jeff-walking-left-09.png", "jeff-walking/jeff-walking-left-10.png", "jeff-walking/jeff-walking-left-11.png",
		"jeff-walking/jeff-walking-left-12.png", "jeff-walking/jeff-walking-left-13.png", "jeff-walking/jeff-walking-left-14.png",
		"jeff-walking/jeff-walking-left-15.png", "jeff-walking/jeff-walking-left-16.png", "jeff-walking/jeff-walking-left-17.png",
		"jeff-walking/jeff-walking-left-18.png", "jeff-walking/jeff-walking-left-19.png", "jeff-walking/jeff-walking-left-20.png",
		"jeff-walking/jeff-walking-left-21.png", "jeff-walking/jeff-walking-left-22.png", "jeff-walking/jeff-walking-left-23.png",
		"jeff-walking/jeff-walking-left-24.png", "jeff-walking/jeff-walking-left-25.png", "jeff-walking/jeff-walking-left-26.png",
		"jeff-walking/jeff-walking-left-27.png", "jeff-walking/jeff-walking-left-28.png", "jeff-walking/jeff-walking-left-29.png",
		"jeff-walking/jeff-walking-left-30.png", "jeff-walking/jeff-walking-left-31.png", "jeff-walking/jeff-walking-left-32.png",
		"jeff-walking/jeff-walking-left-33.png", "jeff-walking/jeff-walking-left-34.png", "jeff-walking/jeff-walking-left-35.png",
		"jeff-walking/jeff-walking-left-36.png", "jeff-walking/jeff-walking-left-37.png", "jeff-walking/jeff-walking-left-38.png",
		"jeff-walking/jeff-walking-left-39.png", "jeff-walking/jeff-walking-left-40.png", "jeff-walking/jeff-walking-left-41.png",
		"jeff-walking/jeff-walking-left-42.png", "jeff-walking/jeff-walking-left-43.png", "jeff-walking/jeff-walking-left-44.png"
	};
	static constexpr const char* jeff_shooting[] = {
		"jeff_shooting/jeff_shooting_00.png", "jeff_shooting/jeff_shooting_01.png", "jeff_shooting/jeff_shooting_02.png",
		"jeff_shooting/jeff_shooting_03.png", "jeff_shooting/jeff_shooting_04.png", "jeff_shooting/jeff_shooting_05.png",
		"jeff_shooting/jeff_shooting_06.png", "jeff_shooting/jeff_shooting_07.png", "jeff_shooting/jeff_shooting_08.png",
		"jeff_shooting/jeff_shooting_09.png", "jeff_shooting/jeff_shooting_10.png", "jeff_shooting/jeff_shooting_11.png",
		"jeff_shooting/jeff_shooting_12.png", "jeff_shooting/jeff_shooting_13.png", "jeff_shooting/jeff_shooting_14.png",
		"jeff_shooting/jeff_shooting_15.png", "jeff_shooting/jeff_shooting_16.png", "jeff_shooting/jeff_shooting_17.png",
		"jeff_shooting/jeff_shooting_18.png", "jeff_shooting/jeff_shooting_19.png", "jeff_shooting/jeff_shooting_20.png",
		"jeff_shooting/jeff_shooting_21.png", "jeff_shooting/jeff_shooting_22.png", "jeff_shooting/jeff_shooting_23.png",
		"jeff_shooting/jeff_shooting_24.png", "jeff_shooting/jeff_shooting_25.png", "jeff_shooting/jeff_shooting_26.png",
		"jeff_shooting/jeff_shooting_27.png", "jeff_shooting/jeff_shooting_28.png", "jeff_shooting/jeff_shooting_29.png",
		"jeff_shooting/jeff_shooting_30.png", "jeff_shooting/jeff_shooting_31.png", "jeff_shooting/jeff_shooting_32.png",
		"jeff_shooting/jeff_shooting_33.png", "jeff_shooting/jeff_shooting_34.png", "jeff_shooting/jeff_shooting_35.png",
		"jeff_shooting/jeff_shooting_36.png", "jeff_shooting/jeff_shooting_37.png", "jeff_shooting/jeff_shooting_38.png",
		"jeff_shooting/jeff_shooting_39.png", "jeff_shooting/jeff_shooting_40.png", "jeff_shooting/jeff_shooting_41.png",
		"jeff_shooting/jeff_shooting_42.png", "jeff_shooting/jeff_shooting_43.png"
	};

	sf::Texture jeff_standing_texture;
	sf::Texture jeff_standing_left_texture;
	sf::Texture jeff_walking_textures[std::size(jeff_walking)];
	sf::Texture jeff_walking_left_textures[std::size(jeff_walking_left)];
	sf::Texture jeff_shooting_textures[std::size(jeff_shooting)];
};
