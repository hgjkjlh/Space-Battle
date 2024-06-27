#include "player.h"
#include <raylib.h>
#include <math.h>
#include <ctime>

Player::Player() {
	active = true;
	block = false;
	position.x = 500;
	position.y = 500;
	speed.x = 0;
	speed.y = 0;
	f_speed = 6.0f;
	acceleration = 0;
	a_rotation = 360;
	rotation = 360;
	max_bullets = 100;
	bullets[max_bullets];
	shoot_timer = clock();
	health = 400;
	treatment_count = clock();
	texture = LoadTexture(".\\player.png");
}

void Player::Draw() {
	Rectangle sourceRec = { 0.0f, 0.0f, (float)20, (float)30 };
	Rectangle destRec = { position.x, position.y, 20, 30 };
	Vector2 origin = { (float)10, (float)20 };

	DrawTexturePro(texture, sourceRec, destRec, origin, (float)rotation, WHITE);
}

void Player::Move() {

	a_rotation = (atan2(GetMouseX() - position.x, GetMouseY() - position.y) * -57.29578f) + 180;

	if (a_rotation > rotation) {
		if ((a_rotation - rotation) < (360 - a_rotation + rotation)) {
			rotation += 3;
		}
		else {
			rotation -= 3;
		}
	}
	else if (rotation > a_rotation) {
		if ((rotation - a_rotation) < (360 - rotation + a_rotation)) {
			rotation -= 3;
		}
		else {
			rotation += 3;
		}
	}
	if (rotation > 360) {
		rotation = 0;
	}
	if (rotation < 0) {
		rotation = 360;
	}

	if (IsKeyDown(KEY_W) and block == false)
	{
		speed.x = sin(rotation * DEG2RAD) * f_speed;
		speed.y = cos(rotation * DEG2RAD) * f_speed;
		if (acceleration < 1) acceleration += 0.04f;
	}
	else
	{
		if (acceleration > 0) acceleration -= 0.02f;
		else if (acceleration < 0) acceleration = 0;
	}
	if (IsKeyDown(KEY_S) and block == false)
	{
		if (acceleration > 0) acceleration -= 0.03f;
		else if (acceleration < 0) acceleration = 0;
	}

	position.x += (speed.x * acceleration);
	position.y -= (speed.y * acceleration);

	if (position.x > GetScreenWidth() + 20) position.x = -(20);
	else if (position.x < -(20)) position.x = GetScreenWidth() + 20;
	if (position.y > (GetScreenHeight() + 20)) position.y = -(20);
	else if (position.y < -(20)) position.y = GetScreenHeight() + 20;
}

void Player::Shoot() {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) and clock() - shoot_timer > 100) {
		for (int i = 0; i < max_bullets; ++i) {
			if (bullets[i].active == false) {
				bullets[i].position = position;
				bullets[i].speed.x = 2 * sin((180 - rotation) * DEG2RAD) * 6.0f;
				bullets[i].speed.y = 2 * cos((180 - rotation) * DEG2RAD) * 6.0f;
				bullets[i].active = true;
				break;
			}
		}
		shoot_timer = clock();
	}
}

void Player::DrawRoundBullet() {
	for (int i = 0; i < max_bullets; ++i) {
		if (bullets[i].active == true) {
			bullets[i].Draw();
		}
	}
}

void Player::UpdateRoundBullet() {
	for (int i = 0; i < max_bullets; ++i) {
		if (bullets[i].position.x < 0 or bullets[i].position.x > GetScreenWidth() or bullets[i].position.y <0 or bullets[i].position.y > GetScreenHeight()) {
			bullets[i].active = false;
		}
		if (bullets[i].active == true) {
			bullets[i].Update();
		}
	}
}