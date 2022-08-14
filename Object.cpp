#include "Object.h"

void Object::render(sf::RenderWindow& wind) {
	Circle c(float(hitbox.size.x) / 2.0f);
	c.setPosition(float(hitbox.pos.x), float(hitbox.pos.y));
	c.setFillColor(col_to_sf_color(GREEN));
	wind.draw(c);
}