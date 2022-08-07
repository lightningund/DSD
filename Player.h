#pragma once

#ifndef PLAYER
#define PLAYER

#include "Lib.h"
#include "Weapon.h"

class Player {
private:
	const int width{50};
	const int height{50};
	int max_health{100};
	int health{100};
	Weapon wep;
	Vec2 pos; //Position
	Vec2 dir; //Facing direction
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
#endif //!PLAYER