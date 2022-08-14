#pragma once

#include "Lib.h"
#include "Weapon.h"
#include "Damageable.h"

class Player : Damageable {
private:
	const int width{50};
	const int height{50};
	Weapon wep{};
	Vec2 pos{}; //Position
	Vec2 dir{}; //Facing direction
public:
	Player();
	void shoot();
	void show(sf::RenderWindow&);
	void update();
	void move(double, double);
	void move(Vec2);
	void face(double, double);
	void face(Vec2);
	Vec2 getPos();
	Vec2 getCenter();
};
