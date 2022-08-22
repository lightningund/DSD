#include "Lib.h"

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

template <typename T>
void Vec2G<T>::operator+= (Vec2G<T> a) {
	x += a.x;
	y += a.y;
}

template <typename T>
void Vec2G<T>::operator-= (Vec2G<T> a) {
	x -= a.x;
	y -= a.y;
}

template <typename T>
void Vec2G<T>::operator*= (T a) {
	x *= a;
	y *= a;
}

template <typename T>
void Vec2G<T>::operator/= (T a) {
	x /= a;
	y /= a;
}

template <typename T>
Vec2G<T> Vec2G<T>::operator+ (Vec2G<T> a) {
	return Vec2G<T>{x + a.x, y + a.y};
}

template <typename T>
Vec2G<T> Vec2G<T>::operator- (Vec2G<T> a) {
	return Vec2{x - a.x, y - a.y};
}

template <typename T>
Vec2G<T> Vec2G<T>::operator* (T a) {
	return Vec2{x * a, y * a};
}

template <typename T>
Vec2G<T> Vec2G<T>::operator/ (T a) {
	return Vec2{x / a, y / a};
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

// I wrote this code and I don't want to lose it so I'm stashing it away here for the moment
// bool Hitbox::point_overlaps(Vec2 point) {
//	bool x_overlap = point.x > pos.x && point.x < pos.x + size.x;
//	bool y_overlap = point.y > pos.y && point.y < pos.y + size.y;
//	return x_overlap && y_overlap;
// }
