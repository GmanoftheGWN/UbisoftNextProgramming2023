#include "stdafx.h"
#include "../App/app.h"
#include "Bomb.h"


Bomb::Bomb()
{
	objectSize = 20.0f;
	timeUntilDetonation = 3000.0f;
	isDetonated = false;
	timeUntilExplosionEnds = 2000.0f;
}

Bomb::~Bomb()
{
}

void Bomb::Update(float deltaTime_)
{
	if (bombType != BOMB_TYPE::LANDMINE) { timeUntilDetonation -= deltaTime_; }
	if (isDetonated == true) { timeUntilExplosionEnds -= deltaTime_; }
}

void Bomb::Render()
{
	float a = 1.0f;
	float r = 1.0f;
	float g = 0.7f;
	float b = 0.0f;

	float sx, sy, ex, ey;

	//Draw bomb "x"
	sx = pos.x - objectSize / 2;
	sy = pos.y + objectSize / 2;
	ex = pos.x + objectSize / 2;
	ey = pos.y - objectSize / 2;
	App::DrawLine(sx, sy, ex, ey, r, g, b);
	sx = pos.x - objectSize / 2;
	sy = pos.y - objectSize / 2;
	ex = pos.x + objectSize / 2;
	ey = pos.y + objectSize / 2;
	App::DrawLine(sx, sy, ex, ey, r, g, b);
}