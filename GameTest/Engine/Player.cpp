#include "stdafx.h"
#include "Player.h"
#include "../App/app.h"

Player::Player()
{
	objectSize = 25.0f;
	moveSpeed = 2.5f;
	selectedBombType = BOMB_TYPE::NORMAL;
}

Player::~Player()
{
}

void Player::Update(float deltaTime_) 
{
	prevPos = pos;

	if (App::GetController().GetLeftThumbStickY() < -0.5f) { pos.y += moveSpeed; }		//"W"
	if (App::GetController().GetLeftThumbStickX() < -0.5f) { pos.x -= moveSpeed; }		//"A"
	if (App::GetController().GetLeftThumbStickY() > 0.5f) { pos.y -= moveSpeed; }		//"S"
	if (App::GetController().GetLeftThumbStickX() > 0.5f) { pos.x += moveSpeed; }		//"D"
	

	if (App::GetController().CheckButton(XINPUT_GAMEPAD_LEFT_THUMB, true)) { selectedBombType = BOMB_TYPE::NORMAL; }		//"1"
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_RIGHT_THUMB, true)) { selectedBombType = BOMB_TYPE::DIRECTIONAL; }	//"2"
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_LEFT_SHOULDER, true)) { selectedBombType = BOMB_TYPE::LANDMINE; }	//"3"
}

void Player::Render()
{
	float a = 1.0f;
	float r = 0.0f;
	float g = 1.0f;
	float b = 0.0f;

	float sx, sy, ex, ey;

	//Draw player triangle
	sx = pos.x;
	sy = pos.y + objectSize / 2;
	ex = pos.x + objectSize / 2;
	ey = pos.y - objectSize / 2;
	App::DrawLine(sx, sy, ex, ey, r, g, b);
	sx = pos.x + objectSize / 2;
	sy = pos.y - objectSize / 2;
	ex = pos.x - objectSize / 2;
	ey = pos.y - objectSize / 2;
	App::DrawLine(sx, sy, ex, ey, r, g, b);
	sx = pos.x - objectSize / 2;
	sy = pos.y - objectSize / 2;
	ex = pos.x;
	ey = pos.y + objectSize / 2;
	App::DrawLine(sx, sy, ex, ey, r, g, b);
}
