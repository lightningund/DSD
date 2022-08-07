#include "Lib.h"

Col color(int gray) {
	Col col = { gray, gray, gray, 255 };
	return col;
}

Col color(int gray, int alpha) {
	Col col = { gray, gray, gray, alpha };
	return col;
}

Col color(int red, int green, int blue) {
	Col col = { red, green, blue, 255 };
	return col;
}

Col color(int red, int green, int blue, int alpha) {
	Col col = { red, green, blue, alpha };
	return col;
}

int gcd(int a, int b) {
	int gcd = 0;
	bool exit = false;

	while (!exit) {
		if (a > b) {
			a -= b;
		}
		else if (b > a) {
			b -= a;
		}
		else {
			gcd = a;
			exit = true;
		}
	}
	return gcd;
}

int lcm(int a, int b) {
	return 0;
}

bool isPrime(int n) {
	return false;
}

int limitVal(int limitee, int limit) {
	if (limitee > limit) {
		limitee = limit;
	}
	else if (limitee < -limit) {
		limitee = -limit;
	}
	return limitee;
}

int limitVal(int limitee, int upperLim, int lowerLim) {
	return 0;
}

bool isLimited(int limitee, int limit) {
	return (limitee < -limit || limitee > limit);
}

bool isLimited(int limitee, int upperLim, int lowerLim) {
	return (limitee < lowerLim || limitee > upperLim);
}

bool overlap(float ax, float ay, float aw, float ah, float bx, float by, float bw, float bh) {
	return((ax + aw > bx && ax < bx + bw) && (ay + ah > by && ay < by + bh));
}

float getAngle(Vec2f vec) {
	return atan2f(vec.x, vec.y);
}

float radiansToDegrees(float radians) {
	return radians * 360 / 6.28;
}