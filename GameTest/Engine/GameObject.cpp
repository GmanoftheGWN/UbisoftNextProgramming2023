#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject() : parent(nullptr), pos(Vec3(0.0f))
{
}

GameObject::~GameObject() 
{
}

bool GameObject::Init() 
{ 
	return true; 
}

void GameObject::Update(float deltaTime_)
{
}

void GameObject::Render()
{
}

void GameObject::Shutdown() 
{
}

