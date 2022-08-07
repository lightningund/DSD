#include "Lib.h"

Col color(uint8_t gray) {
	Col col{gray, gray, gray, 255};
	return col;
}

Col color(uint8_t gray, uint8_t alpha) {
	Col col{gray, gray, gray, alpha};
	return col;
}

Col color(uint8_t red, uint8_t green, uint8_t blue) {
	Col col{red, green, blue, 255};
	return col;
}

Col color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
	Col col{red, green, blue, alpha};
	return col;
}

void Vec2::operator+= (Vec2 a) {
	x += a.x;
	y += a.y;
}
void Vec2::operator-= (Vec2 a) {
	x -= a.x;
	y -= a.y;
}
void Vec2::operator*= (double a) {
	x *= a;
	y *= a;
}
void Vec2::operator/= (double a) {
	x /= a;
	y /= a;
}
Vec2 Vec2::operator+ (Vec2 a) {
	return Vec2{x + a.x, y + a.y};
}
Vec2 Vec2::operator- (Vec2 a) {
	return Vec2{x - a.x, y - a.y};
}
Vec2 Vec2::operator* (double a) {
	return Vec2{x * a, y * a};
}
Vec2 Vec2::operator/ (double a) {
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
	return atan2f((float)vec.x, (float)vec.y);
}

double radiansToDegrees(double radians) {
	return radians * 360 / 6.28;
}

sf::Color col_to_sf_color(Col col) {
	sf::Color sf_col{col.r, col.g, col.b, col.a};
	return sf_col;
}