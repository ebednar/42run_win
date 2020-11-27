#include "42run.h"
#include "engine.h"
#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void	camera_controls(Engine	*eng)
{
	eng->cam.speed = 2.5f * eng->delta_time;
	if (eng->controls.keys[GLFW_KEY_W])
		eng->cam.pos += eng->cam.speed * eng->cam.front;
	if (eng->controls.keys[GLFW_KEY_S])
		eng->cam.pos -= eng->cam.speed * eng->cam.front;
	if (eng->controls.keys[GLFW_KEY_A])
		eng->cam.pos -= eng->cam.speed * glm::normalize(glm::cross(eng->cam.front, eng->cam.up));
	if (eng->controls.keys[GLFW_KEY_D])
		eng->cam.pos += eng->cam.speed * glm::normalize(glm::cross(eng->cam.front, eng->cam.up));
	//eng->cam.yaw = eng->controls.yaw;
	//eng->cam.pitch = eng->controls.pitch;
}

void	game_loop(Engine *eng)
{
	eng->scene[0]->rotate(30 * eng->delta_time, 0.0f, 0.0f);
	camera_controls(eng);
}

int		main(void)
{
	Engine	engine;
	Entity	*ent = new Entity();
	Entity	*player = new Entity();

	engine.init_engine(WIDTH, HEIGHT);

	ent->set_model("res/models/test.obj");
	engine.add_entity(ent);

	engine.run_engine(game_loop);
	return 0;
}
