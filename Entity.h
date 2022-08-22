#pragma once

#include <SFML/Graphics.hpp>
#include "Hitbox.h"
#include "Lib.h"

class Entity {
public:
	sf::Texture texture;
	sf::Sprite sprite;
	Hitbox hitbox;
	void render(sf::RenderWindow& wind);
};
