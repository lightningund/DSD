#pragma once

#include <SFML/Graphics.hpp>
#include "Lib.h"

namespace Components {
	// Just a hitbox
	typedef struct Hitbox {
		Vec2 pos{};
		Vec2 size{};
		bool has_collision{true};
	} Hitbox;

	// For anything that needs to be effected by physics
	typedef struct Moveable {
		Vec2 vel{};
		Vec2 acc{};
	} Moveable;

	// For anything that needs to take damage
	typedef struct Health {
		double max_health{};
		double health{};
	} Health;

	// For... Debugging right now. I'll get back to this
	typedef struct Sign {
		std::string text{};
	} Sign;

	typedef struct Weapon {
		double dmg{};
		double fire_rate{};
		int ammo_reserve_max{};
		int ammo_reserve{};
		int magazine_max{};
		int magazine{};
	} Weapon;

	// It's a sprite "set" because it needs both a sprite and a texture
	typedef struct SpriteSet {
		sf::Texture texture{};
		sf::Sprite sprite{};
	} SpriteSet;

	// For marking an entity as the player, contains no data, essentially just a flag
	typedef struct Player {} Player;
}
