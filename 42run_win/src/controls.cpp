#include "42run.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void	shift_player(Engine* eng, float speed, int side)
{
	
	eng->state->shifting_x += side * speed * sin(glm::radians(eng->player->angle[1]));
	eng->state->shifting_y += side * speed * cos(glm::radians(eng->player->angle[1]));
	std::cout << "x " << eng->state->shifting_x << std::endl;
	std::cout << "y " << eng->state->shifting_y << std::endl;
	if (eng->state->shifting_x >= 1.0f)
	{
		eng->state->shifting_x = 1.0f;
		return;
	}
	if (eng->state->shifting_x <= -1.0f)
	{
		eng->state->shifting_x = 1.0f;
		return;
	}
	if (eng->state->shifting_y >= 1.0f)
	{
		eng->state->shifting_y = 1.0f;
		return;
	}
	if (eng->state->shifting_y <= -1.0f)
	{
		eng->state->shifting_y = -1.0f;
		return;
	}
	eng->player->move(side * speed * sin(glm::radians(eng->player->angle[1])), 0.0f, side * speed * cos(glm::radians(eng->player->angle[1])));
}

void	controls(Engine* eng)
{
	float speed = glm::pi<float>() * eng->delta_time;
	eng->player->move(speed * cos(glm::radians(eng->player->angle[1])), 0.0f, -speed * sin(glm::radians(eng->player->angle[1])));
	if (eng->free_cam)
	{
		eng->cam.speed = 8.0f * eng->delta_time;
		if (eng->controls.keys[GLFW_KEY_W])
			eng->cam.pos += eng->cam.speed * eng->cam.front;
		if (eng->controls.keys[GLFW_KEY_S])
			eng->cam.pos -= eng->cam.speed * eng->cam.front;
		if (eng->controls.keys[GLFW_KEY_A])
			eng->cam.pos -= eng->cam.speed * glm::normalize(glm::cross(eng->cam.front, eng->cam.up));
		if (eng->controls.keys[GLFW_KEY_D])
			eng->cam.pos += eng->cam.speed * glm::normalize(glm::cross(eng->cam.front, eng->cam.up));
		eng->cam.yaw = eng->controls.yaw;
		eng->cam.pitch = eng->controls.pitch;
	}
	else
	{
		if (eng->controls.keys[GLFW_KEY_A])
			shift_player(eng, speed, -1);
		if (eng->controls.keys[GLFW_KEY_D])
			shift_player(eng, speed, 1);
		eng->cam.pos.x = eng->player->position[0];
		eng->cam.pos.z = eng->player->position[2];
		eng->cam.yaw = -eng->player->angle.y;
	}
}
