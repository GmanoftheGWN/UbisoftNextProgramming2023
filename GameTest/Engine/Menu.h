#ifndef MENU_H
#define MENU_H

#include "Level.h"

class Menu : public Level
{
public:
	Menu();
	~Menu();

	bool Init();
	void Update(float deltaTime);
	void Render() override;
	void Shutdown();
};
#endif
