#pragma once
#include "Entity.h"
#include <vector>
class Render
{
public:
	void AddEntity(Entity *ent);
	void DrawScene();

public:
private:
	std::vector<Entity*> scene;
};
