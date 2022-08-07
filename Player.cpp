#include "Player.h"

Player::Player() : pos{100, 100}, dir{1, 0}, wep{10, 10} {}

void Player::shoot() {}

void Player::show(sf::RenderWindow& wind) {
	Circle c(width / 2.0f);
	c.setPosition((float)pos.x, (float)pos.y);
	c.setFillColor(col_to_sf_color(BLUE));
	wind.draw(c);
}

void Player::update() {}

void Player::move(double dx, double dy) {
	this->move(Vec2{dx, dy});
}

void Player::move(Vec2 d) {
	this->pos += d;
}

void Player::face(double dx, double dy) {
	this->face(Vec2{dx, dy});
}
void Player::face(Vec2 d) {
	this->dir = d;
}

Vec2 Player::getPos() {
	return pos;
}

Vec2 Player::getCenter() {
	return pos + Vec2{(double)width / 2, (double)height / 2};
}
