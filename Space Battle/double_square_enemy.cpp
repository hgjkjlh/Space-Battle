#include "double_square_enemy.h"
#include <raylib.h>
#include <cmath>
#include <time.h>

Double_square_enemy::Double_square_enemy() {
	active = false;
	block = false;
	timer = clock();
	position = { -1000,-1000 };
	speed = { 0,0 };
	f_speed = 3.0f;
	size = 30;
	rotation = 0;
	max_rockets = 100;
	rockets[max_rockets];
	shoot_timer = clock();
	health = 100;
	texture = LoadTexture(".\\double_square_enemy.png");
}

void Double_square_enemy::Draw() {
	DrawTexture(texture, position.x - size / 2, position.y - size / 2, WHITE);
}

void Double_square_enemy::Update(Player player) {
	rotation = (atan2(player.position.x - position.x, player.position.y - position.y) * -57.29578f) + 180;

	if (block == true and (clock() - timer > 500)) {
		block = false;
		timer = clock();
	}

	if (block == false) {
		speed.x = sin(rotation * DEG2RAD) * f_speed;
		speed.y = -(cos(rotation * DEG2RAD) * f_speed);
	}

	position.x += speed.x;
	position.y += speed.y;

	if (position.x > GetScreenWidth() + 75) position.x = -(45);
	else if (position.x < -(75)) position.x = GetScreenWidth() + 45;
	if (position.y > (GetScreenHeight() + 75)) position.y = -(45);
	else if (position.y < -(75)) position.y = GetScreenHeight() + 45;

	if (health <= 0) {
		active = false;
	}
}

void Double_square_enemy::Shoot() {
	if (clock() - shoot_timer > 2000) {
		for (int i = 0; i < max_rockets; ++i) {
			if (rockets[i].active == false) {
				rockets[i].position = position;
				rockets[i].speed.x = 2 * sin((180 - rotation) * DEG2RAD) * 6.0f;
				rockets[i].speed.y = 2 * cos((180 - rotation) * DEG2RAD) * 6.0f;
				rockets[i].active = true;
				rockets[i].timer = clock();
				rockets[i].burst = false;
				break;
			}
		}
		shoot_timer = clock();
	}
}

void Double_square_enemy::DrawRocket() {
	for (int i = 0; i < max_rockets; ++i) {
		if (rockets[i].active == true) {
			rockets[i].Draw();
		}
	}
}

void Double_square_enemy::UpdateRoket(Player &player) {
	for (int i = 0; i < max_rockets; ++i) {
		if (rockets[i].position.x < 0 or rockets[i].position.x > GetScreenWidth() or rockets[i].position.y <0 or rockets[i].position.y > GetScreenHeight()) {
			rockets[i].active = false;
		}
		if (rockets[i].active == true) {
			rockets[i].Update(player);
		}
	}
}

void Double_square_enemy::Reset() {
	active = true;
	block = false;
	timer = clock();
	speed = { 0,0 };
	f_speed = 3.0f;
	size = 30;
	rotation = 0;
	shoot_timer = clock();
	health = 100;
}