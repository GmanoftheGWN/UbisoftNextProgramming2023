#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"

enum class MOVEMENT_DIRECTION
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
};

class Enemy : public GameObject
{
public:
	MOVEMENT_DIRECTION movementDirection;
	int currentTileIndex;
	int targetTileIndex;

	Enemy();
	~Enemy();

	void Update(float deltaTime_) override;
	void Render() override;
};
#endif