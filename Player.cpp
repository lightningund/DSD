#include "Player.h"

Player::Player() {
	shooting = false;
	pos = Vec2f{ 100, 100 };
	dir = Vec2f{ 1, 0 };
	wep = Weapon(10, 10);
}

void Player::shoot() {
	if (!shot) {
		shooting = true;
		shot = true;
	}
}

void Player::show(sf::RenderWindow& wind) {
	Circle c(width / 2, height / 2);
	c.setPosition(pos.x, pos.y);
	c.setFillColor(BLUE);
	wind.draw(c);

	if (shooting) {
		wep.shoot(wind, dir, pos + Vec2f{float(width / 2), float(height / 2)});
	}
}

void Player::update() {
	shooting = false;
	if (shot) {
		if (shotTimer >= 60 / wep.getFireRate()) {
			shot = false;
			shotTimer = 0;
		}
		else {
			shotTimer ++;
		}
	}
}

void Player::move(float dx, float dy) {
	this->move(Vec2f{ dx, dy });
}

void Player::move(Vec2f d) {
	this->pos += d;
}

void Player::face(float dx, float dy) {
	this->face(Vec2f{ dx, dy });
}
void Player::face(Vec2f d) {
	this->dir = d;
}

Vec2f Player::getPos() {
	return pos;
}

Vec2f Player::getCenter() {
	return pos + Vec2f{(float)width / 2, (float)height / 2};
}

float Player::getX() {
	return pos.x;
}

float Player::getY() {
	return pos.y;
}