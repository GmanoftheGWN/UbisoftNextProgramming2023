#ifndef LEVEL_H
#define LEVEL_H

#include "../App/app.h"
#include "Player.h"
#include "Enemy.h"
#include "Bomb.h"

enum class LEVEL_TYPE 
{
	MENU = 0,
	NORMAL,
	CHALLENGE,
	BOSS,
};

class Level 
{
public:
	Player player;
	std::vector<Enemy> enemies;
	std::vector<Bomb> bombs;
	bool directionalBombRequiresDirection = false;

	virtual ~Level() {}
	virtual bool Init() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Shutdown() = 0;
};
#endif