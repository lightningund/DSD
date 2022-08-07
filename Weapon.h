#pragma once

#ifndef WEAPON
#define WEAPON

#include <SFML/Graphics.hpp>

#include "Lib.h"

static class Weapon {
protected:
	float dmg, bulletSpeed, fireRate;
	int bulletType, numBullets;
public:
	Weapon();
	Weapon(float dmg, float fireRate);
	void shoot(RWind&);
	void shoot(RWind&, Vec2f);
	void shoot(RWind&, Vec2f, Vec2f);
	float getFireRate();
};
#endif //!WEAPON