#include <SFML/Graphics.hpp>
#include <iostream>

#include "Lib.hpp"
#include "SceneView.hpp"
#include "Components.hpp"
#include "EntityManager.hpp"

constexpr Vec2 INV_VEC = Vec2{INFINITY, INFINITY};

void update(sf::RenderWindow& wind, EntityManager& manager);
void render(sf::RenderWindow& wind, EntityManager& manager);

using namespace Components;

sf::Font font{};

// Nothing in here has any comments because it is in constant flux
int main() {
	font.loadFromFile("res/UbuntuMono-Regular.ttf");
	constexpr auto WIDTH{800};
	constexpr auto HEIGHT{800};
	constexpr auto STAT_UPDATE_RATE{0.5};

	int frame_counter{0};
	sf::Int64 frame_time_counter{0};

	sf::RenderWindow window{sf::VideoMode(WIDTH, HEIGHT), "Deep Sea Death"};

	sf::Clock clk{};

	EntityManager manager{};
	
	EntityID player = manager.create_entity();
	auto player_hbox = manager.assign_component<Hitbox>(player);
	auto player_health = manager.assign_component<Health>(player);
	auto player_player = manager.assign_component<Player>(player);
	auto player_primary = manager.assign_component<Primary>(player);
	auto player_secondary = manager.assign_component<Secondary>(player);
	auto player_melee = manager.assign_component<Melee>(player);
	auto player_spriteset = manager.assign_component<SpriteSet>(player);
	auto player_ammo_disp = manager.assign_component<AmmoDisplay>(player);
	auto player_health_disp = manager.assign_component<HealthDisplay>(player);
	manager.assign_component<Moveable>(player);

	player_hbox->pos = Vec2{100, 100};
	player_hbox->size = Vec2{50, 50};
	player_health->health = 100;
	player_health->max_health = 100;
	player_spriteset->texture.loadFromFile("res/sprites/player.png");
	player_spriteset->sprite.setTexture(player_spriteset->texture);
	player_ammo_disp->target = player_player;
	player_health_disp->target = player_health;

	player_primary->ammo_reserve_max = 200;
	player_primary->ammo_reserve = 200;
	player_primary->magazine_max = 20;
	player_primary->magazine = 20;
	player_primary->dmg = 5;
	player_primary->attack_speed = 5.0;
	player_primary->reload_time = 2.0;
	player_player->weapons.push_back(player_primary);
	player_player->curr_wep = player_primary;
	player_player->curr_type = PRIMARY;

	player_secondary->ammo_reserve_max = 100;
	player_secondary->ammo_reserve = 100;
	player_secondary->magazine_max = 10;
	player_secondary->magazine = 10;
	player_secondary->dmg = 5;
	player_secondary->attack_speed = 0.5;
	player_secondary->reload_time = 1.0;
	player_player->weapons.push_back(player_secondary);

	player_melee->attack_speed = 1.2;
	player_melee->dmg = 20;
	player_melee->range = 2;
	player_player->weapons.push_back(player_melee);

	EntityID sign = manager.create_entity();
	auto sign_hbox = manager.assign_component<Hitbox>(sign);
	auto sign_spriteset = manager.assign_component<SpriteSet>(sign);
	auto sign_health = manager.assign_component<Health>(sign);
	manager.assign_component<Sign>(sign);

	sign_hbox->pos = Vec2{200, 100};
	sign_hbox->size = Vec2{50, 50};
	sign_health->health = 100;
	sign_health->max_health = 100;
	sign_spriteset->texture.loadFromFile("res/sprites/sign.png");
	sign_spriteset->sprite.setTexture(sign_spriteset->texture);

	EntityID sign2 = manager.create_entity();
	auto sign2_hbox = manager.assign_component<Hitbox>(sign2);
	auto sign2_spriteset = manager.assign_component<SpriteSet>(sign2);
	manager.assign_component<Sign>(sign2);

	sign2_hbox->pos = Vec2{300, 100};
	sign2_hbox->size = Vec2{50, 50};
	sign2_spriteset->texture.loadFromFile("res/sprites/sign.png");
	sign2_spriteset->sprite.setTexture(sign2_spriteset->texture);

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

			window.clear();

			update(window, manager);

			render(window, manager);

			window.display();
		}
	}

	return 0;
}

void move_entity(const Vec2 movement, const EntityID entity, const EntityManager& manager) {
	auto hbox = manager.get_component<Hitbox>(entity);
	hbox->pos += movement;
}

void damage_entity(const double amnt, const EntityID entity, const EntityManager& manager) {
	auto health = manager.get_component<Health>(entity);
	health->health -= amnt;
}

Vec2 cast_ray(Vec2 ray_pos, Vec2 ray_dir, Vec2 line_a, Vec2 line_b) {
	double x1 = line_a.x;
	double y1 = line_a.y;
	double x2 = line_b.x;
	double y2 = line_b.y;

	double dir_len = ray_dir.get_length();

	double x3 = ray_pos.x;
	double y3 = ray_pos.y;
	double x4 = ray_pos.x + (ray_dir.x / dir_len);
	double y4 = ray_pos.y + (ray_dir.y / dir_len);

	double denom = ((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4));
	if (denom == 0) return INV_VEC;

	double u = ((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denom;
	if (u >= 0) return INV_VEC;

	double t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom;
	if (t <= 0 || t >= 1) return INV_VEC;

	return Vec2{x1 + t * (x2 - x1), y1 + t * (y2 - y1)};
}

EntityID find_shot_intersection(const Vec2 ray_pos, const Vec2 ray_dir, const EntityID origin, EntityManager& manager) {
	Vec2 hit{};
	EntityID hit_ent = EntityID(-1);

	double min_dist = INFINITY;

	ComponentMask health_mask = create_mask<Health, Hitbox>();
	for (EntityID entity : SceneView(manager, health_mask)) {
		if(entity == origin) continue;

		auto hbox = manager.get_component<Hitbox>(entity);
		std::vector<Vec2> corners = {
			hbox->pos,
			hbox->pos + Vec2{hbox->size.x, 0},
			hbox->pos + hbox->size,
			hbox->pos + Vec2{0, hbox->size.y}
		};

		for (int i = 0; i < 4; i ++) {
			Vec2 c = cast_ray(ray_pos, ray_dir, corners[i], corners[(i + 1) % 4]);
			if(c == INV_VEC) continue;

			double d = (c - ray_pos).get_sq_length();
			if (d < min_dist) {
				min_dist = d;
				hit = c;
				hit_ent = entity;
			}
		}
	}

	return hit_ent;
}

void player_reload(Player* player) {
	if (player->curr_type == MELEE) return;

	Gun* wep = (Gun*)player->curr_wep;
	if (wep->reloading) return;
	if (wep->magazine == wep->magazine_max) return;

	std::cout << "Player Reloading!\n";

	wep->reloading = true;
	wep->reload_clock.restart();
}

void player_check_finished_reloading(Player* player) {
	if (player->curr_type == MELEE) return;

	Gun* wep = (Gun*)player->curr_wep;
	if (!wep->reloading) return;

	if (wep->reload_clock.getElapsedTime().asMicroseconds() > 1000000 * wep->reload_time) {
		std::cout << "Player Finished Reloading!\n";

		wep->reloading = false;
		int bullets_refilled = min(std::vector<int>{wep->magazine_max - wep->magazine, wep->ammo_reserve});
		wep->ammo_reserve -= bullets_refilled;
		wep->magazine += bullets_refilled;
	};
}

void shoot(const EntityID player, sf::RenderWindow& wind, EntityManager& manager) {
	auto player_player = manager.get_component<Player>(player);
	if(player_player->curr_type == MELEE) return;

	Gun* wep = (Gun*)(player_player->curr_wep);

	if (wep->reloading) return;

	if (wep->attack_clock.getElapsedTime().asMicroseconds() >= 1000000 / wep->attack_speed) {
		wep->attack_clock.restart();

		if (wep->magazine > 0) {
			wep->magazine --;
			auto player_hbox = manager.get_component<Hitbox>(player);

			Vec2 line_start = player_hbox->pos + player_hbox->size / 2;

			sf::VertexArray line{sf::Lines, 2};
			line[0].position = vec2_to_sf_vec2f(line_start);
			line[1].position = vec2_to_sf_vec2f(line_start + player_player->target_dir.set_length(1000));

			line[0].color = col_to_sf_color(WHITE);
			line[1].color = col_to_sf_color(WHITE);

			wind.draw(line);

			EntityID hit_ent = find_shot_intersection(line_start, player_player->target_dir, player, manager);

			if (hit_ent != EntityID(-1)) {
				auto target_health = manager.get_component<Health>(hit_ent);
				target_health->health -= wep->dmg;
			}
		} else {
			player_reload(player_player);
		}
	}
}

void update(sf::RenderWindow& wind, EntityManager& manager) {
	sf::Event event;
	while (wind.pollEvent(event)) {
		if (event.type == sf::Event::Closed) wind.close();
		/*else if (event.type == sf::Event::MouseWheelMoved) {
			std::cout << event.mouseWheel.delta << "\n";
		}*/
	}

	Vec2 mouse_pos{M::getPosition(wind)};

	ComponentMask player_mask = create_mask<Player>();
	for (EntityID player : SceneView(manager, player_mask)) {
		auto player_player = manager.get_component<Player>(player);
		auto player_hbox = manager.get_component<Hitbox>(player);
		player_player->target_dir = mouse_pos - (player_hbox->pos + player_hbox->size / 2);

		player_check_finished_reloading(player_player);

		if(KB::isKeyPressed(KB::R)) player_reload(player_player);

		Vec2 movement{};
		if (KB::isKeyPressed(KB::W)) movement += Vec2{0, -1};
		if (KB::isKeyPressed(KB::A)) movement += Vec2{-1, 0};
		if (KB::isKeyPressed(KB::S)) movement += Vec2{0, 1};
		if (KB::isKeyPressed(KB::D)) movement += Vec2{1, 0};

		if (movement != Vec2{0, 0}) {
			move_entity(movement * 10, player, manager);
		}

		if (M::isButtonPressed(M::Left)) {
			//damage_entity(1, player, manager);
			shoot(player, wind, manager);
		}
	}
	
	if (KB::isKeyPressed(KB::Escape)) {
		wind.close();
	}
}

void draw_sprites(sf::RenderWindow& wind, EntityManager& manager) {
	ComponentMask renderable_mask = create_mask<Hitbox, SpriteSet>();
	for (EntityID entity : SceneView(manager, renderable_mask)) {
		auto hbox = manager.get_component<Hitbox>(entity);
		auto spriteset = manager.get_component<SpriteSet>(entity);

		spriteset->sprite.setPosition(vec2_to_sf_vec2f(hbox->pos));
		spriteset->sprite.setScale(vec2_to_sf_vec2f(hbox->size / 32.0));
		wind.draw(spriteset->sprite);
	}
}

// Draw a single healthbar
void draw_healthbar(sf::RenderWindow& wind, const double health_percent, const double x, const double y, const double width, const double height) {
	float trim = float(height) * 0.1f;
	Rect bar_bg{{float(width), float(height)}};
	bar_bg.setPosition(float(x), float(y));
	bar_bg.setFillColor(col_to_sf_color(GREY));
	Rect bar{bar_bg};
	bar.move(trim, trim);
	bar.setSize({(float(width) - trim * 2) * float(health_percent), float(height) - trim * 2});
	bar.setFillColor(col_to_sf_color(RED));
	wind.draw(bar_bg);
	wind.draw(bar);
}

// Draw healthbars of all entities
void draw_healthbars(sf::RenderWindow& wind, EntityManager& manager) {
	ComponentMask healthbar_mask = create_mask<Health>();
	for (EntityID entity : SceneView(manager, healthbar_mask)) {
		constexpr auto healthbar_height = 20;

		auto hbox = manager.get_component<Hitbox>(entity);
		auto health = manager.get_component<Health>(entity);
		double health_percent = health->health / health->max_health;

		draw_healthbar(wind, health_percent, hbox->pos.x, hbox->pos.y + hbox->size.y, hbox->size.x, healthbar_height);
	}
}

// Draw all the UI elements
void draw_ui(sf::RenderWindow& wind, EntityManager& manager) {
	// The healthbar
	ComponentMask health_disp_mask = create_mask<HealthDisplay>();
	for (EntityID entity : SceneView(manager, health_disp_mask)) {
		auto disp = manager.get_component<HealthDisplay>(entity);
		auto healthbar_width = wind.getSize().x * 0.15;
		auto healthbar_height = healthbar_width * 0.2;
		auto healthbar_trim = healthbar_height * 0.1;
		auto healthbar_padding = healthbar_trim * 5;
		auto healthbar_x = wind.getSize().x - healthbar_width - healthbar_padding;
		auto healthbar_y = healthbar_padding;

		auto health = disp->target;
		auto health_percent = health->health / health->max_health;

		draw_healthbar(wind, health_percent, healthbar_x, healthbar_y, healthbar_width, healthbar_height);
	}

	// The ammo counter
	ComponentMask ammo_disp_mask = create_mask<AmmoDisplay>();
	for (EntityID entity : SceneView(manager, health_disp_mask)) {
		auto disp = manager.get_component<AmmoDisplay>(entity);
		auto player = disp->target;

		if (player->curr_type != MELEE) {
			Gun* wep = (Gun*)player->curr_wep;
			sf::Text text;
			text.setFont(font);
			text.setPosition(wind.getSize().x * 0.8f, wind.getSize().y * 0.9f);
			text.setString(wep->magazine + std::string("/") + wep->ammo_reserve);
			text.setCharacterSize(24);
			text.setFillColor(col_to_sf_color(WHITE));
			wind.draw(text);
		}
	}
}

void render(sf::RenderWindow& wind, EntityManager& manager) {
	draw_sprites(wind, manager);
	draw_healthbars(wind, manager);
	draw_ui(wind, manager);
}
