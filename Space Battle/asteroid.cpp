#include "asteroid.h"
#include <raylib.h>
#include <random>

Asteroid::Asteroid() {
    active = false;
    position = { -100,-100 };
    speed = { 0,0 };
    radius = 0;
    health = 0;
}

void Asteroid::Draw() {
    DrawTexture(texture, position.x - radius, position.y - radius, WHITE);
}

void Asteroid::Update() {
    position.x += speed.x;
    position.y += speed.y;
}

Vector2 Asteroid::GetPosition(int var) {
    float posx, posy;
    bool correctRange = false;

    if (var == 1) {
        posx = GetRandomValue(-radius * 2, GetScreenWidth() + radius * 2);
        while (!correctRange)
        {
            if (posx > -radius && posx < GetScreenWidth() + radius) posx = GetRandomValue(-radius * 2, GetScreenWidth() + radius * 2);
            else correctRange = true;
        }
        posy = GetRandomValue(-radius * 2, GetScreenHeight() + radius * 2);
    }
    else {
        posy = GetRandomValue(-radius * 2, GetScreenHeight() + radius * 2);
        while (!correctRange)
        {
            if (posy > -radius && posy < GetScreenHeight() + radius) posy = GetRandomValue(-radius * 2, GetScreenHeight() + radius * 2);
            else correctRange = true;
        }
        posx = GetRandomValue(-radius * 2, GetScreenWidth() + radius * 2);
    }

    Vector2 position = { posx, posy };

    return position;
}

Vector2 Asteroid::GetSpeed(int type) {
    float velx, vely;
    float velocity;
    switch (type) {
    case 1:
        velocity = 1;
        break;
    case 2:
        velocity = 2;
        break;
    case 3:
        velocity = 3;
        break;
    }
    bool correctRange = false;

    velx = GetRandomValue(-velocity, velocity) / 1.7;
    vely = GetRandomValue(-velocity, velocity) / 1.7;

    while (!correctRange)
    {
        if (velx == 0 && vely == 0)
        {
            velx = GetRandomValue(-velocity, velocity) / 1.7;
            vely = GetRandomValue(-velocity, velocity) / 1.7;
        }
        else correctRange = true;
    }

    Vector2 speed = { velx, vely };

    return speed;
}