#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"

class Damageable : public Object {
protected:
	const double max_health{100};
	double health{100};
public:
	void render(sf::RenderWindow& wind);
	void take_damage(double dmg);
	double health_percent();
};
