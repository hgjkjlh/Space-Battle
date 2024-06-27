#pragma once
#include <raylib.h>
#include <vector>

class Asteroid
{
public:
    Asteroid();
    bool active;
    Vector2 position;
    Vector2 speed;
    float radius;
    int health;
    void Draw();
    void Update();
    Texture2D texture;
    Vector2 GetPosition(int var);
    Vector2 GetSpeed(int type);
};