#pragma once

#include <SFML/Graphics.hpp>

#include "Lib.h"

class Weapon {
protected:
	double dmg{};
	double bullet_speed{};
	double fire_rate{};
	int num_bullets{};
public:
	Weapon();
	Weapon(double dmg, double fire_rate);
};
