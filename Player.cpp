#include "Player.h"

Player::Player() : dir{1, 0} {
	hitbox.size = Vec2{50, 50};
	hitbox.pos = Vec2{100, 100};
}

void Player::shoot() {}

void Player::render(sf::RenderWindow& wind) {
	Damageable::render(wind);
	Circle c(float(hitbox.size.x) / 2.0f);
	c.setPosition(float(hitbox.pos.x), float(hitbox.pos.y));
	c.setFillColor(col_to_sf_color(BLUE));
	wind.draw(c);
}

void Player::update() {}

void Player::move(double dx, double dy) {
	move(Vec2{dx, dy} * 10);
}

void Player::move(Vec2 d) {
	hitbox.pos += d;
}

void Player::face(double dx, double dy) {
	face(Vec2{dx, dy});
}
void Player::face(Vec2 d) {
	dir = d;
}
