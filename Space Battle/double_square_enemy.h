#pragma once
#include "player.h"
#include "rocket.h"

class Double_square_enemy
{
public:
	Double_square_enemy();
	bool active;
	bool block;
	int timer;
	Vector2 position;
	Vector2 speed;
	float f_speed;
	float size;
	float rotation;
	int max_rockets;
	Rocket rockets[100];
	int shoot_timer;
	int health;
	Texture2D texture;
	void Draw();
	void Update(Player player);
	void Shoot();
	void DrawRocket();
	void UpdateRoket(Player &player);
	void Reset();
};