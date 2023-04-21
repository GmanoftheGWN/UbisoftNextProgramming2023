#include "stdafx.h"
#include "GameManager.h"
#include "Menu.h"
#include "NormalLevel.h"

GameManager::GameManager() : currentLevel(nullptr)
{
	levelType = LEVEL_TYPE::MENU;
}

GameManager::~GameManager() 
{
}

bool GameManager::Init()
{
	BuildLevel(levelType);

	return true;
}

void GameManager::Update(float deltaTime)
{
	//Freeze game until player gives a direction to the directional bomb
	if (currentLevel->directionalBombRequiresDirection)
	{
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, true))
		{
			currentLevel->bombs[currentLevel->bombs.size() - 1].directionalBombDirection = DIRECTIONAL_BOMB_DIRECTION::UP;
			currentLevel->directionalBombRequiresDirection = false;
		}
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, true))
		{
			currentLevel->bombs[currentLevel->bombs.size() - 1].directionalBombDirection = DIRECTIONAL_BOMB_DIRECTION::DOWN;
			currentLevel->directionalBombRequiresDirection = false;
		}
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, true))
		{
			currentLevel->bombs[currentLevel->bombs.size() - 1].directionalBombDirection = DIRECTIONAL_BOMB_DIRECTION::LEFT;
			currentLevel->directionalBombRequiresDirection = false;
		}
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, true))
		{
			currentLevel->bombs[currentLevel->bombs.size() - 1].directionalBombDirection = DIRECTIONAL_BOMB_DIRECTION::RIGHT;
			currentLevel->directionalBombRequiresDirection = false;
		}
		return;
	}

	currentLevel->Update(deltaTime);
}

void GameManager::Render()
{
	currentLevel->Render();

	if (levelType == LEVEL_TYPE::MENU) { return; }

	//Add the in level informational text
	char textBuffer[64];
	sprintf(textBuffer, "Level: %d", playerStats.levelsCleared + 1);
	App::Print(475.0f, 730.0f, textBuffer, 0.0f, 0.5f, 1.0f, GLUT_BITMAP_TIMES_ROMAN_24);
	sprintf(textBuffer, "Lives: %d", playerStats.livesRemaining);
	App::Print(75.0f, 730.0f, textBuffer, 0.0f, 0.5f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	sprintf(textBuffer, "Enemies: %d", currentLevel->enemies.size());
	App::Print(875.0f, 730.0f, textBuffer, 0.0f, 0.5f, 1.0f, GLUT_BITMAP_HELVETICA_18);

	if (currentLevel->player.selectedBombType == BOMB_TYPE::NORMAL)
	{
		sprintf(textBuffer, "Selected Bomb Type: Normal");
		App::Print(675.0f, 30.0f, textBuffer, 0.0f, 0.5f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	}
	if (currentLevel->player.selectedBombType == BOMB_TYPE::DIRECTIONAL)
	{
		sprintf(textBuffer, "Selected Bomb Type: Directional");
		App::Print(675.0f, 30.0f, textBuffer, 0.0f, 0.5f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	}
	if (currentLevel->player.selectedBombType == BOMB_TYPE::LANDMINE)
	{
		sprintf(textBuffer, "Selected Bomb Type: Landmine");
		App::Print(675.0f, 30.0f, textBuffer, 0.0f, 0.5f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	}
}

void GameManager::Shutdown()
{
	currentLevel->Shutdown();
}

void GameManager::BuildLevel(LEVEL_TYPE level_)
{
	switch (level_) {
	case LEVEL_TYPE::MENU:
		currentLevel = std::make_shared<Menu>();
		currentLevel->Init();
		levelType = LEVEL_TYPE::MENU;
		break;

	case LEVEL_TYPE::NORMAL:
		TileSystem::getInstance()->Reset();
		currentLevel = std::make_shared<NormalLevel>();
		currentLevel->Init();
		levelType = LEVEL_TYPE::NORMAL;
		break;

	default:
		currentLevel = nullptr;
		break;
	}
}