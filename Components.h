#pragma once

#include <SFML/Graphics.hpp>
#include "Lib.h"

namespace Components {
	struct Hitbox {
		Vec2 pos{};
		Vec2 size{};
		bool has_collision{true};
	};

	struct Damageable {
		const double max_health{100};
		double health{100};
	};

	struct Sign {
		std::string text;
	};

	struct Weapon {
		double dmg{};
		double bullet_speed{};
		double fire_rate{};
		int num_bullets{};
	};

	struct Renderable {
		sf::Texture texture;
		sf::Sprite sprite;
	};
}