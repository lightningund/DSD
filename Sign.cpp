#include "Sign.h"

Sign::Sign() {
	hitbox.size = Vec2{50, 50};
	hitbox.pos = Vec2{200, 100};

	texture.loadFromFile("./res/sprites/sign.png");
	sprite.setTexture(texture);
}