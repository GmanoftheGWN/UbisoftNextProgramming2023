#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <memory>
#include <random>
#include "Level.h"
#include "PlayerStats.h"
#include "TileSystem.h"

class GameManager 
{
private:
	static GameManager* GameManagerInstance;

	std::shared_ptr<Level> currentLevel;

public:
	static GameManager* getInstance() 
	{
		if (!GameManagerInstance) 
		{
			GameManagerInstance = new GameManager();
		}
		return GameManagerInstance;
	}

	std::random_device generator;

	LEVEL_TYPE levelType;
	PlayerStats playerStats;

	GameManager();
	~GameManager();

	bool Init();
	void Update(float deltaTime);
	void Render();
	void Shutdown();

	void BuildLevel(LEVEL_TYPE level_);

	std::shared_ptr<Level> getCurrentLevel() { return currentLevel; }
};
#endif