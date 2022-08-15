#pragma once

#include "Lib.h"
#include "Weapon.h"
#include "Damageable.h"

class Player : public Damageable {
private:
	Weapon wep{};
	Vec2 dir{}; //Facing direction
public:
	Player();
	void shoot();
	void update();
	void move(double, double);
	void move(Vec2);
	void face(double, double);
	void face(Vec2);
	Vec2 get_pos();
};
