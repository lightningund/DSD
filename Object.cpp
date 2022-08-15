#include "Object.h"

void Object::render(sf::RenderWindow& wind) {
	sprite.setPosition(vec2_to_sf_vec2f(hitbox.pos));
	sprite.setScale(vec2_to_sf_vec2f(hitbox.size / 32.0));
	wind.draw(sprite);
}

std::string Object::test() {
	return "obj";
}