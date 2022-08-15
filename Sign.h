#pragma once

#include <SFML/Graphics.hpp>
#include "Damageable.h"

class Sign : public Damageable {
private:
	std::string text;
public:
	Sign();
};