#pragma once
#include <vector>
#include "bullet.h"

class Player
{
public:
	Player();
	bool active;
	bool block;
	Vector2 position;
	Vector2 speed;
	float f_speed;
	float acceleration;
	float a_rotation;
	float rotation;
	int max_bullets;
	Bullet bullets[100];
	int shoot_timer;
	int health;
	int treatment_count;
	Texture2D texture;
	void Draw();
	void Move();
	void Shoot();
	void DrawRoundBullet();
	void UpdateRoundBullet();
};