#include "Lib.h"

Col color(int gray) {
	Col col{gray, gray, gray, 255};
	return col;
}

Col color(int gray, int alpha) {
	Col col{gray, gray, gray, alpha};
	return col;
}

Col color(int red, int green, int blue) {
	Col col{red, green, blue, 255};
	return col;
}

Col color(int red, int green, int blue, int alpha) {
	Col col{red, green, blue, alpha};
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

double limitVal(double limitee, double upperLim, double lowerLim) {
	return 0;
}

bool isLimited(double limitee, double limit) {
	return (limitee < -limit || limitee > limit);
}

bool isLimited(double limitee, double upperLim, double lowerLim) {
	return (limitee < lowerLim || limitee > upperLim);
}

bool overlap(double ax, double ay, double aw, double ah, double bx, double by, double bw, double bh) {
	return((ax + aw > bx && ax < bx + bw) && (ay + ah > by && ay < by + bh));
}

double getAngle(Vec2 vec) {
	return atan2f(vec.x, vec.y);
}

double radiansToDegrees(double radians) {
	return radians * 360 / 6.28;
}