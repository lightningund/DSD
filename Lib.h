#pragma once

#include <SFML/Graphics.hpp>

typedef sf::CircleShape Circle;
typedef sf::RectangleShape Rect;
typedef sf::RenderWindow RWind;
typedef sf::Window Wind;
typedef sf::Keyboard KB;
typedef sf::Mouse M;

//Color
typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} Col;

//2D-Vector with doubles
struct Vec2{
	double x{};
	double y{};

	void operator+= (Vec2 a);
	void operator-= (Vec2 a);
	void operator*= (double a);
	void operator/= (double a);
	Vec2 operator+ (Vec2 a);
	Vec2 operator- (Vec2 a);
	Vec2 operator* (double a);
	Vec2 operator/ (double a);
};

//2D-Vector with ints
typedef sf::Vector2i Vec2i;

// Generate a new Color object with grayscale input with full opacity
Col color(uint8_t gray);

// Generate a new Color object with grayscale and alpha input
Col color(uint8_t gray, uint8_t alpha);

// Generate a new Color object with red, green, and blue inputs and full opacity
Col color(uint8_t red, uint8_t green, uint8_t blue);

// Generate a new Color object with red, green, blue, and alpha inputs
Col color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

// Generate a new Color object with red, green, blue, and alpha inputs, all in one number
Col color(uint32_t val);

//Limit a number
double limitVal(double limitee, double limit);

//Limit a number with different upper and lower bounds
double limitVal(double limitee, double upper_lim, double lower_lim);

//Check if a number is outside of bounds
bool isLimited(double limitee, double limit);

//Check if a number is outside of different upper and lower bounds
bool isLimited(double limitee, double upper_lim, double lower_lim);

//Check if 2 squares overlap
bool overlap(double ax, double ay, double aw, double ah, double bx, double by, double bw, double bh);

//Find the angle of a vector
double getAngle(Vec2);

// Convert an input in radians into degrees
double radiansToDegrees(double radians);

// Convert Col struct to sf::Color object
sf::Color col_to_sf_color(Col col);

constexpr Col BLACK{0, 0, 0, 255};
constexpr Col GREY{128, 128, 128, 255};
constexpr Col WHITE{255, 255, 255, 255};
constexpr Col RED{255, 0, 0, 255};
constexpr Col GREEN{0, 255, 0, 255};
constexpr Col BLUE{0, 0, 255, 255};
constexpr Col YELLOW{255, 255, 0, 255};
constexpr Col PURPLE{255, 0, 255, 255};
constexpr Col CYAN{0, 255, 255, 255};
constexpr Col ORANGE{255, 128, 0, 255};
