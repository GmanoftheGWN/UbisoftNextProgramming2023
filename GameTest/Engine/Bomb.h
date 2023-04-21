#ifndef BOMB_H
#define BOMB_H

#include "GameObject.h"
#include <vector>

enum class BOMB_TYPE
{
	NORMAL = 0,
	DIRECTIONAL,
	LANDMINE,
};

enum class DIRECTIONAL_BOMB_DIRECTION
{
	UP = 0,
	DOWN,
	LEFT,
	RIGHT,
};

class Bomb : public GameObject
{
public:
	BOMB_TYPE bombType;
	DIRECTIONAL_BOMB_DIRECTION directionalBombDirection;
	float timeUntilDetonation;
	bool isDetonated;
	float timeUntilExplosionEnds;
	std::vector<int> affectedTileIndices;

	Bomb();
	~Bomb();

	void Update(float deltaTime_) override;
	void Render() override;

};
#endif
