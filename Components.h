#pragma once

#include <SFML/Graphics.hpp>
#include "Lib.h"

namespace Components {
	typedef struct Hitbox {
		Vec2 pos{};
		Vec2 size{};
		bool has_collision{true};
	} Hitbox;

	typedef struct Moveable {
		Vec2 vel{};
		Vec2 acc{};
	} Moveable;

	typedef struct Health {
		const double max_health{100};
		double health{100};
	} Health;

	typedef struct Sign {
		std::string text;
	} Sign;

	typedef struct Weapon {
		double dmg{};
		double bullet_speed{};
		double fire_rate{};
		int num_bullets{};
	} Weapon;

	typedef struct SpriteSet {
		sf::Texture texture;
		sf::Sprite sprite;
	} SpriteSet;

	typedef struct Player {} Player;
}
