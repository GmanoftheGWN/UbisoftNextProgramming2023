#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Bomb.h"

class Player : public GameObject
{
public:
	BOMB_TYPE selectedBombType;

	Player();
	~Player();

	void Update(float deltaTime_) override;
	void Render() override;

};
#endif

