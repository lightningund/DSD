#pragma once

#ifndef WEAPON
#define WEAPON

#include <SFML/Graphics.hpp>

#include "Lib.h"

class Weapon {
protected:
	double dmg{0};
	double bullet_speed{0};
	double fire_rate{0};
	int num_bullets{0};
public:
	Weapon();
	Weapon(double dmg, double fire_rate);
};
#endif //!WEAPON