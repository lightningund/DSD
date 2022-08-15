#include "Player.h"

Player::Player() : dir{1, 0} {
	hitbox.size = Vec2{50, 50};
	hitbox.pos = Vec2{100, 100};

	texture.loadFromFile("./res/sprites/player.png");
	sprite.setTexture(texture);
}

void Player::shoot() {}

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

Vec2 Player::get_pos() {
	return hitbox.pos;
}