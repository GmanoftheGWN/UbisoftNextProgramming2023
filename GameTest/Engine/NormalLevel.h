#ifndef NORMALLEVEL_H
#define NORMALLEVEL_H

#include "Level.h"
 
class NormalLevel : public Level
{
public:
	NormalLevel();
	~NormalLevel();

	bool Init();
	void Update(float deltaTime);
	void Render();
	void Shutdown();

	void SpawnBomb();
	void CreateExplosion(int bombIndex_);
	void SpawnEnemies(int numberOfEnemies_);
};
#endif
