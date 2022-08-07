#pragma once

#ifndef PLAYER
#define PLAYER

#include "Lib.h"
#include "Mech.h"
#include "Weapon.h"

class Player {
private:
	const int width = 50;
	const int height = 50;
	const int shotCooldown = 30;
	int shotTimer = 0;
	Weapon wep;
	Mech mech;
	Vec2f pos;  //Position
	Vec2f dir; //Facing direction
	bool shooting; //Debug
	bool shot;
public:
	Player();
	void shoot();
	void show(sf::RenderWindow&);
	void update();
	void move(float, float);
	void move(Vec2f);
	void face(float, float);
	void face(Vec2f);
	Vec2f getPos();
	Vec2f getCenter();
	float getX();
	float getY();
};
#endif //!PLAYER