#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>
#include "../math/Vec3.h"

using namespace MATH;

class GameObject 
{
protected:
	std::shared_ptr<GameObject> parent;

public:
	Vec3 pos;
	Vec3 prevPos;
	float objectSize;
	float moveSpeed;

	GameObject();
	virtual ~GameObject();

	virtual bool Init();
	virtual void Update(float deltaTime_);
	virtual void Render();
	virtual void Shutdown();

};
#endif