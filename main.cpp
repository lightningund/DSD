#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

#include "Lib.h"
#include "Weapon.h"
#include "Player.h"

constexpr auto WIDTH = 800;
constexpr auto HEIGHT = 800;
constexpr auto frameUpdateTime = 0.5;

sf::RenderWindow* wind;

int frameCount = 0;
int frameCountCounter = 0;
double frameRate;
sf::Int64 frameTime;
sf::Int64 frameTimeCounter = 0;

Player player;

void update();
void render();

int main() {
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Deep Sea Death");

	wind = &window;

	sf::Clock clk;

	while (window.isOpen()) { //Main Loop
		if (clk.getElapsedTime().asMicroseconds() >= (1000000 / 60)) {
			frameTimeCounter += clk.getElapsedTime().asMicroseconds();
			frameCountCounter ++;

			if (frameTimeCounter >= 1000000 * frameUpdateTime) {
				frameTime = clk.getElapsedTime().asMicroseconds();
				frameTimeCounter = 0;
				frameRate = frameCountCounter / frameUpdateTime;
				frameCountCounter = 0;
				std::cout << frameTime / 1000 << "ms " << frameRate << "fps\n";
			}
			clk.restart();

			update();
			render();
		}
	}

	return 0;
}

void update() {
	sf::Event event;
	while (wind->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			wind->close();
		}
	}

	player.update();

	if (KB::isKeyPressed(KB::W)) {
		player.move(0, -1);
	}
	if (KB::isKeyPressed(KB::A)) {
		player.move(-1, 0);
	}
	if (KB::isKeyPressed(KB::S)) {
		player.move(0, 1);
	}
	if (KB::isKeyPressed(KB::D)) {
		player.move(1, 0);
	}
	if (M::isButtonPressed(M::Left)) {
		//player.shoot();
		player.take_damage(10);
	}
	if (KB::isKeyPressed(KB::Escape)) {
		wind->close();
	}
	sf::Vector2i MP = M::getPosition(*wind);
	//player.face(((MP.x - player.getCenter().x) / 10), ((MP.y - player.getCenter().y) / 10));
}

void render() {
	wind->clear();
	player.render(*wind);
	wind->display();
}
