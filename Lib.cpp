#include "Lib.h"

ComponentID component_counter{0};

Col color(const uint8_t gray) {
	return Col{gray, gray, gray, 255};
}

Col color(const uint8_t gray, const uint8_t alpha) {
	return Col{gray, gray, gray, alpha};
}

Col color(const uint8_t red, const uint8_t green, const uint8_t blue) {
	return Col{red, green, blue, 255};
}

Col color(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t alpha) {
	return Col{red, green, blue, alpha};
}

Col color(const uint32_t val) {
	Col col{val >> 24, (val >> 16) & 0xFF, (val >> 8) & 0xFF, val & 0xFF};
	return col;
}

double limit_val(const double limitee, const double limit) {
	if (limitee > limit) return limit;
	else if (limitee < -limit) return -limit;

	return limitee;
}

double limit_val(const double limitee, const double upper_lim, const double lower_lim) {
	if (limitee > upper_lim) return upper_lim;
	else if (limitee < lower_lim) return lower_lim;

	return limitee;
}

bool is_limited(const double limitee, const double limit) {
	return (limitee < -limit || limitee > limit);
}

bool is_limited(const double limitee, const double upper_lim, const double lowerLim) {
	return (limitee < lowerLim || limitee > upper_lim);
}

bool overlap(const double ax, const double ay, const double aw, const double ah, const double bx, const double by, const double bw, const double bh) {
	return((ax + aw > bx && ax < bx + bw) && (ay + ah > by && ay < by + bh));
}

double get_angle(const Vec2 vec) {
	return atan2f(float(vec.x), float(vec.y));
}

double get_slope(const Vec2 vec) {
	return vec.y / vec.x;
}

Vec2 vec_from_angle(const double angle) {
	return Vec2{sin(angle), cos(angle)};
}

double radians_to_degrees(const double radians) {
	return radians * 360 / 6.28;
}

sf::Color col_to_sf_color(const Col col) {
	return sf::Color{col.r, col.g, col.b, col.a};;
}

sf::Vector2f vec2_to_sf_vec2f(const Vec2 vec) {
	return sf::Vector2f{float(vec.x), float(vec.y)};
}

bool mask_check(const ComponentMask subject, const ComponentMask goal) {
	return (subject & goal) == goal;
}

std::string operator+(const std::string str, const int num) {
	return str + std::to_string(num);
}

std::string operator+(const std::string str, const double num) {
	return str + std::to_string(num);
}

std::string operator+(const int num, const std::string str) {
	return std::to_string(num) + str;
}

std::string operator+(const double num, const std::string str) {
	return std::to_string(num) + str;
}
