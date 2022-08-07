#pragma once

#ifndef METHLIB
#define METHLIB

#include<SFML/Graphics.hpp>

#define BLACK sf::Color(0, 0, 0, 255)
#define GREY sf::Color(128, 128, 128, 255)
#define WHITE sf::Color(255, 255, 255, 255)
#define RED sf::Color(255, 0, 0, 255)
#define GREEN sf::Color(0, 255, 0, 255)
#define BLUE sf::Color(0, 0, 255, 255)
#define YELLOW sf::Color(255, 255, 0, 255)
#define PURPLE sf::Color(255, 0, 255, 255)
#define CYAN sf::Color(0, 255, 255, 255)
#define ORANGE sf::Color(255, 128, 0, 255)

typedef sf::CircleShape Circle;
typedef sf::RectangleShape Rect;
typedef sf::RenderWindow RWind;
typedef sf::Window Wind;
typedef sf::Keyboard KB;
typedef sf::Mouse M;

//Color
typedef struct {
	int r;
	int g;
	int b;
	int a;
} Col;

//2D-Vector with doubles
struct Vec2{
	double x;
	double y;

	void operator += (Vec2 a) {
		this->x += a.x;
		this->y += a.y;
	}
	void operator -= (Vec2 a) {
		this->x -= a.x;
		this->y -= a.y;
	}
	void operator *= (Vec2 a) {
		this->x *= a.x;
		this->y *= a.y;
	}
	void operator /= (Vec2 a) {
		this->x /= a.x;
		this->y /= a.y;
	}
	Vec2 operator + (Vec2 a) {
		return Vec2{ this->x + a.x, this->y + a.y };
	}
	Vec2 operator - (Vec2 a) {
		return Vec2{ this->x - a.x, this->y - a.y };
	}
	Vec2 operator * (double a) {
		return Vec2{ this->x * a, this->y * a };
	}
	Vec2 operator / (double a) {
		return Vec2{ this->x / a, this->y / a };
	}
};

//2D-Vector with ints
typedef sf::Vector2i Vec2i;

//Tetris Piece
typedef struct {
	Vec2i p[4];
} Piece;

//Tetris Piece with all 4 rotations
typedef struct {
	Piece rot[4];
	sf::Color col;
} PieceF;

typedef struct {
	bool on;
	sf::Color col;
	sf::Color prevCol;
} Cell;

Col color(int gray);
Col color(int gray, int alpha);
Col color(int red, int green, int blue);
Col color(int red, int green, int blue, int alpha);

double limitVal(double limitee, double limit); //Limit a number
double limitVal(double limitee, double upperLim, double lowerLim); //Limit a number with different upper and lower bounds
bool isLimited(double limitee, double limit); //Check if a number is outside of bounds
bool isLimited(double limitee, double upperLim, double lowerLim); //Check if a number is outside of different upper and lower bounds
bool overlap(double ax, double ay, double aw, double ah, double bx, double by, double bw, double bh); //Check if 2 squares overlap
double getAngle(Vec2); //Find the angle of a vector
double radiansToDegrees(double radians);
#endif //!METHLIB
