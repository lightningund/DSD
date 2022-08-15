#pragma once

#include <SFML/Graphics.hpp>
#include "Hitbox.h"
#include "Lib.h"

class Object {
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	Hitbox hitbox;
public:
	virtual void render(sf::RenderWindow& wind);
	std::string test();
};
