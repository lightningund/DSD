#pragma once

#include "Lib.h"
#include "Weapon.h"
#include "Damageable.h"

class Player : Damageable {
private:
	Weapon wep{};
	Vec2 dir{}; //Facing direction
public:
	Player();
	void render(sf::RenderWindow& wind);
	void shoot();
	void update();
	void move(double, double);
	void move(Vec2);
	void face(double, double);
	void face(Vec2);
};
