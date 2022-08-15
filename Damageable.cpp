#include "Damageable.h"

constexpr auto healthbar_height = 20;
constexpr auto healthbar_trim = 3;

void Damageable::render(sf::RenderWindow& wind) {
	Object::render(wind);
	Rect bar_bg{{float(hitbox.size.x), float(healthbar_height)}};
	bar_bg.setPosition(float(hitbox.pos.x), float(hitbox.pos.y + hitbox.size.y));
	bar_bg.setFillColor(col_to_sf_color(GREY));
	Rect bar{bar_bg};
	bar.move(healthbar_trim, healthbar_trim);
	bar.setSize({float((hitbox.size.x - healthbar_trim * 2) * health_percent()), float(healthbar_height - healthbar_trim * 2)});
	bar.setFillColor(col_to_sf_color(RED));
	wind.draw(bar_bg);
	wind.draw(bar);
}

void Damageable::take_damage(double dmg) {
	health -= dmg;
}

double Damageable::health_percent() {
	return health / max_health;
}