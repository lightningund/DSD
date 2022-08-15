#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <filesystem>
#include <span>

#include "Lib.h"
#include "Weapon.h"
#include "Player.h"
#include "Sign.h"

void update(sf::RenderWindow& wind, Player& player);
void render_objs(sf::RenderWindow& wind, std::span<Object*> objs);

int main() {
	constexpr auto WIDTH = 800;
	constexpr auto HEIGHT = 800;
	constexpr auto STAT_UPDATE_RATE = 0.5;

	int frame_counter = 0;
	sf::Int64 frame_time_counter = 0;

	std::vector<Object*> objs;

	Player player;
	objs.push_back(&player);

	Sign sign;
	objs.push_back(&sign);

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Deep Sea Death");
	
	sf::Clock clk;

	while (window.isOpen()) { //Main Loop
		if (clk.getElapsedTime().asMicroseconds() >= (1000000 / 60)) {
			frame_time_counter += clk.getElapsedTime().asMicroseconds();
			frame_counter ++;

			if (frame_time_counter >= 1000000 * STAT_UPDATE_RATE) {
				sf::Int64 frame_time = clk.getElapsedTime().asMicroseconds();
				double frame_rate = frame_counter / STAT_UPDATE_RATE;
				frame_time_counter = 0;
				frame_counter = 0;

				std::cout << frame_time / 1000 << "ms " << frame_rate << "fps\n";
			}
			clk.restart();

			update(window, player);

			render_objs(window, objs);
		}
	}

	return 0;
}

void update(sf::RenderWindow& wind, Player& player) {
	sf::Event event;
	while (wind.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			wind.close();
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
		player.shoot();
		//player.take_damage(10);
	}
	if (KB::isKeyPressed(KB::Escape)) {
		wind.close();
	}
	sf::Vector2i MP = M::getPosition(wind);
	//player.face(((MP.x - player.getCenter().x) / 10), ((MP.y - player.getCenter().y) / 10));
}

void render_objs(sf::RenderWindow& wind, std::span<Object*> objs) {
	wind.clear();
	for (Object* obj : objs) {
		obj->render(wind);
	}
	wind.display();
}
