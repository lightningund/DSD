#pragma once

#include <SFML/Graphics.hpp>
#include "Lib.hpp"

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
		sf::Clock attack_clock{};
		double attack_speed{};
		double dmg{};
	} Weapon;

	typedef struct Gun : public Weapon {
		sf::Clock reload_clock{};
		double reload_time{};
		int ammo_reserve_max{};
		int ammo_reserve{};
		int magazine_max{};
		int magazine{};

		bool reloading{false};
	} Gun;

	typedef struct Primary : public Gun {} Primary;

	typedef struct Secondary : public Gun {} Secondary;

	typedef struct Melee : public Weapon {
		double range{};
	} Melee;

	// It's a sprite "set" because it needs both a sprite and a texture
	typedef struct SpriteSet {
		sf::Texture texture{};
		sf::Sprite sprite{};
	} SpriteSet;

	// For marking an entity as the player, contains a pointer to the current weapon
	typedef struct Player {
		Vec2 target_dir{};
		WeaponType curr_type{};
		Weapon* curr_wep{};
		std::vector<Weapon*> weapons{};
	} Player;

	typedef struct AmmoDisplay {
		Player* target{};
	} AmmoDisplay;

	typedef struct HealthDisplay {
		Health* target{};
	} HealthDisplay;
}
