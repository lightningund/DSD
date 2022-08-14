#pragma once

#include <SFML/Graphics.hpp>
#include "Hitbox.h"

class Object {
protected:
	Hitbox hitbox;
public:
	void render(sf::RenderWindow& wind);
};
