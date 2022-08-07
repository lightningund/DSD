#include "Weapon.h"

Weapon::Weapon() : Weapon(10, 10) {}

Weapon::Weapon(float dmg, float fireRate) {
	this->dmg = dmg;
	this->fireRate = fireRate;
}

void Weapon::shoot(RWind& wind) {
	shoot(wind, Vec2f{ 0, 0 }, Vec2f{ 0, 0 });
}

void Weapon::shoot(RWind& wind, Vec2f dir) {
	shoot(wind, dir, Vec2f{ 0, 0 });
}

void Weapon::shoot(RWind& wind, Vec2f dir, Vec2f pos) {
	Rect b(sf::Vector2f(10, 100));
	b.setPosition(pos.x, pos.y);
	b.setFillColor(WHITE);
	b.setRotation(-radiansToDegrees(getAngle(dir)));
	wind.draw(b);
}

float Weapon::getFireRate() {
	return fireRate;
}