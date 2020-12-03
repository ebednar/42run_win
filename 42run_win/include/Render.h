#pragma once
#include "entity.h"
#include <vector>
#include "camera.h"

class Render
{
public:
	Entity *player;
public:
	void	draw_scene(std::vector<Entity *> scene, std::vector<Entity *> lights, Camera *cam, bool free_cam);
private:
};
