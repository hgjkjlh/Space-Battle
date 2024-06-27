#pragma once
#include "player.h"

class Square_enemy
{
public:
	Square_enemy();
	bool active;
	bool a_block;
	bool block;
	int a_timer;
	int timer;
	Vector2 position;
	Vector2 speed;
	float f_speed;
	float size;
	float rotation;
	int health;
	Texture2D texture;
	void Draw();
	void Update(Player player);
	void Reset();
};