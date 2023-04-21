#include "stdafx.h"
#include "GameManager.h"
#include "Menu.h"

Menu::Menu() 
{
}

Menu::~Menu() 
{
}

bool Menu::Init() 
{
	return true;
}

void Menu::Update(float deltaTime) 
{
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_START, true))
	{
		GameManager::getInstance()->BuildLevel(LEVEL_TYPE::NORMAL);
	}
}

void Menu::Render()
{
	App::Print(450.0f, 600.0f, "Bomber Triangle", 0.0f, 1.0f, 0.1f, GLUT_BITMAP_TIMES_ROMAN_24);

	App::Print(300.0f, 500.0f, "Controls: ", 0.0f, 1.0f, 0.1f, GLUT_BITMAP_HELVETICA_18);
	App::Print(300.0f, 450.0f, "Use W,A,S,D to move and press SPACE to place bombs", 0.0f, 1.0f, 0.1f, GLUT_BITMAP_HELVETICA_18);
	App::Print(300.0f, 400.0f, "Press 1 for normal bombs, 2 for directional bombs, and 3 for landmines", 0.0f, 1.0f, 0.1f, GLUT_BITMAP_HELVETICA_18);
	App::Print(300.0f, 350.0f, "Use the arrow keys to choose the direction of the directional bomb", 0.0f, 1.0f, 0.1f, GLUT_BITMAP_HELVETICA_18);

	App::Print(450.0f, 250.0f, "Press ENTER to start", 0.0f, 1.0f, 0.1f, GLUT_BITMAP_HELVETICA_18);
}

void Menu::Shutdown()
{
}
