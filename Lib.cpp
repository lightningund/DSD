#include "Lib.h"

ComponentID component_counter{0};

Col color(uint8_t gray) {
	return Col{gray, gray, gray, 255};
}

Col color(uint8_t gray, uint8_t alpha) {
	return Col{gray, gray, gray, alpha};
}

Col color(uint8_t red, uint8_t green, uint8_t blue) {
	return Col{red, green, blue, 255};
}

Col color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
	return Col{red, green, blue, alpha};
}

Col color(uint32_t val) {
	Col col{val >> 24, (val >> 16) & 0xFF, (val >> 8) & 0xFF, val & 0xFF};
	return col;
}

double limitVal(double limitee, double limit) {
	if (limitee > limit) {
		limitee = limit;
	}
	else if (limitee < -limit) {
		limitee = -limit;
	}
	return limitee;
}

double limitVal(double limitee, double upper_lim, double lower_lim) {
	if (limitee > upper_lim) {
		return upper_lim;
	} else if (limitee < lower_lim) {
		return lower_lim;
	}
	return limitee;
}

bool isLimited(double limitee, double limit) {
	return (limitee < -limit || limitee > limit);
}

bool isLimited(double limitee, double upper_lim, double lowerLim) {
	return (limitee < lowerLim || limitee > upper_lim);
}

bool overlap(double ax, double ay, double aw, double ah, double bx, double by, double bw, double bh) {
	return((ax + aw > bx && ax < bx + bw) && (ay + ah > by && ay < by + bh));
}

double getAngle(Vec2 vec) {
	return atan2f(float(vec.x), float(vec.y));
}

double radiansToDegrees(double radians) {
	return radians * 360 / 6.28;
}

sf::Color col_to_sf_color(Col col) {
	return sf::Color{col.r, col.g, col.b, col.a};;
}

sf::Vector2f vec2_to_sf_vec2f(Vec2 vec) {
	return sf::Vector2f{float(vec.x), float(vec.y)};
}

bool mask_check(ComponentMask subject, ComponentMask goal) {
	return (subject & goal) == goal;
}

std::string operator+(std::string str, int num) {
	return str + std::to_string(num);
}

std::string operator+(std::string str, double num) {
	return str + std::to_string(num);
}

std::string operator+(int num, std::string str) {
	return std::to_string(num) + str;
}

std::string operator+(double num, std::string str) {
	return std::to_string(num) + str;
}
