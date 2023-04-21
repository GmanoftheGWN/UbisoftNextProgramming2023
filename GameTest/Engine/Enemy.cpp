#include "stdafx.h"
#include "../App/app.h"
#include "Enemy.h"

Enemy::Enemy()
{
	objectSize = 30.0f;
	moveSpeed = 0.75f;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime_)
{
	switch (movementDirection)
	{
	case MOVEMENT_DIRECTION::UP:
		pos.y += moveSpeed;
		break;
	case MOVEMENT_DIRECTION::DOWN:
		pos.y -= moveSpeed;
		break;
	case MOVEMENT_DIRECTION::LEFT:
		pos.x -= moveSpeed;
		break;
	case MOVEMENT_DIRECTION::RIGHT:
		pos.x += moveSpeed;
		break;
	default:
		break;
	}
}

void Enemy::Render()
{
	float a = 1.0f;
	float r = 1.0f;
	float g = 0.0f;
	float b = 0.0f;

	float sx, sy, ex, ey;

	//Draw enemy "x"
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
