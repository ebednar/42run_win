#include "42run.h"
#include <time.h>
#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void	controls(Engine	*eng)
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

	//float speed = 5.0f * eng->delta_time;
	//if (eng->controls.keys[GLFW_KEY_W])
	//	eng->player->move(speed * cos(glm::radians(eng->player->angle[1])), 0.0f, -speed * sin(glm::radians(eng->player->angle[1])));
	//if (eng->controls.keys[GLFW_KEY_S])
	//	eng->player->move(-speed * cos(glm::radians(eng->player->angle[1])), 0.0f, speed *sin(glm::radians(eng->player->angle[1])));
	//if (eng->controls.keys[GLFW_KEY_A])
	//	eng->player->rotate(0.0f, 20 * speed, 0.0f);
	//if (eng->controls.keys[GLFW_KEY_D])
	//	eng->player->rotate(0.0f, -20 * speed, 0.0f);

	float speed = 7.0f * eng->delta_time;
		eng->player->move(speed * cos(glm::radians(eng->player->angle[1])), 0.0f, -speed * sin(glm::radians(eng->player->angle[1])));

	/*eng->cam.pos.x = eng->player->position[0];
	eng->cam.pos.z = eng->player->position[2];
	eng->cam.yaw = -eng->player->angle.y;*/
}

void replace_platform(Engine *eng)
{
	int				i;
	int				j;
	unsigned int	k;
	Entity			**ptr;

	k = 0;
	int next = rand() % 3;
	if (next == 1 && eng->state->next != left)
	{
		std::cout << "right" << std::endl;
		eng->state->next = right;
	}
	else if (next == 2 && eng->state->next != right)
	{
		std::cout << "left" << std::endl;
		eng->state->next = left;
	}
	else
	{
		std::cout << "forw" << std::endl;
		eng->state->next = forw;
	}
	if (eng->state->next == forw)
	{
		eng->state->plat_start[0] = eng->state->plat_end[0] + 1.0f;
		eng->state->plat_start[2] = eng->state->plat_end[2];
		for (i = -1; i < 29; ++i)
		{
			for (j = -1; j < 2; ++j)
			{
				eng->state->current_plat[k++]->move_to((float)i + eng->state->plat_end[0], -1.05f, (float)j + eng->state->plat_end[2]);
			}
		}
		eng->state->plat_end[0] += 29.0f;
	}
	else if (eng->state->next == right)
	{
		eng->state->plat_start[0] = eng->state->plat_end[0];
		eng->state->plat_start[2] = eng->state->plat_end[2] + 1.0f;
		for (i = -1; i < 29; ++i)
		{
			for (j = -1; j < 2; ++j)
			{
				eng->state->current_plat[k++]->move_to((float)j + eng->state->plat_end[0], -1.05f, (float)i + eng->state->plat_end[2]);
			}
		}
		eng->state->plat_end[2] += 29.0f;
	}
	else
	{
		eng->state->plat_start[0] = eng->state->plat_end[0];
		eng->state->plat_start[2] = eng->state->plat_end[2] - 1.0f;
		for (i = -1; i < 29; ++i)
		{
			for (j = -1; j < 2; ++j)
			{
				eng->state->current_plat[k++]->move_to((float)j + eng->state->plat_end[0], -1.05f, eng->state->plat_end[2] - (float)i);
			}
		}
		eng->state->plat_end[2] -= 29.0f;
	}
	std::cout << eng->state->plat_end[0] << " " << eng->state->plat_end[2] << std::endl;
	std::cout << eng->state->plat_start[0] << " " << eng->state->plat_start[2] << std::endl;
	
	ptr = eng->state->current_plat;
	eng->state->current_plat = eng->state->next_plat;
	eng->state->next_plat = ptr;
}

void	rotate_player(Engine* eng)
{
	eng->state->frames++;
	if (eng->state->current == right)
	{
		std::cout << "rotate right" << std::endl;
		eng->player->rotate(0.0f, -90.0f * eng->delta_time, 0.0f);
		

	}
	else if (eng->state->current == left)
	{
		std::cout << "rotate left" << std::endl;
		eng->player->rotate(0.0f, 90.0f * eng->delta_time, 0.0f);
	}
	else
	{
		std::cout << "rotate forw" << std::endl;
		eng->player->rotate(0.0f, 0.0f, 0.0f);
	}
	if (eng->state->frames == 60)
	{
		eng->state->frames = 0;
		eng->player->move_to(eng->state->p_new_pos[0], eng->player->position.y, eng->state->p_new_pos[2]);
		eng->state->rotate = false;
		eng->state->current = eng->state->next;
	}
}

void	game_loop(Engine *eng)
{
	if (abs(eng->player->position.x + eng->player->position.z - eng->state->plat_start[0] - eng->state->plat_start[2]) < 0.5f)
	{
		std::cout << "replace" << std::endl;
		eng->state->rotate = true;
		eng->state->p_new_pos[0] = eng->state->plat_start[0];
		eng->state->p_new_pos[1] = eng->state->plat_start[1];
		eng->state->p_new_pos[2] = eng->state->plat_start[2];
		replace_platform(eng);
	}
	if (eng->state->rotate)
		rotate_player(eng);
	controls(eng);
}

void	create_platform(Engine *eng, state* state)
{
	Model			*platform_mod = new Model();
	int				i;
	int				j;
	unsigned int	k;

	platform_mod->load_obj("res/models/test.obj", true);
	platform_mod->set_shader("res/shaders/stand_vertex.glsl", "res/shaders/stand_fragment.glsl");
	platform_mod->load_texture("res/textures/wall.jpg");
	eng->add_model(platform_mod);
	state->current_plat = new Entity * [30 * 3];
	state->next_plat = new Entity * [30 * 3];
	k = 0;
	for (i = -1; i < 29; ++i)
	{
		for (j = -1; j < 2; ++j)
		{
			Entity* platform = new Entity();
			platform->set_model(platform_mod);
			eng->add_entity(platform);
			platform->scale(1.0f, 0.1f, 1.0f);
			platform->move_to((float)i + state->plat_end[0], -1.05f, (float)j + state->plat_end[2]);
			state->current_plat[k++] = platform;
		}
	}
	state->plat_end[0] += 29.0f;
	state->plat_start[0] += 30.0f;
	k = 0;
	for (i = -1; i < 29; ++i)
	{
		for (j = -1; j < 2; ++j)
		{
			Entity* platform = new Entity();
			platform->set_model(platform_mod);
			eng->add_entity(platform);
			platform->scale(1.0f, 0.1f, 1.0f);
			platform->move_to((float)i + state->plat_end[0], -1.05f, (float)j + state->plat_end[2]);
			state->next_plat[k++] = platform;
		}
	}
	state->plat_end[0] += 29.0f;
}

void	init_game(Engine *eng, state *state)
{
	Entity	*player = new Entity();
	Entity	*light = new Entity();
	
	Model	*player_mod = new Model();
	Model	*light_mod = new Model();

	player_mod->load_obj("res/models/test.obj", true);
	player_mod->set_shader("res/shaders/stand_vertex.glsl", "res/shaders/stand_fragment.glsl");
	player_mod->load_texture("res/textures/wall.jpg");

	light_mod->load_obj("res/models/test.obj", true);
	light_mod->set_shader("res/shaders/light_vertex.glsl", "res/shaders/light_fragment.glsl");
	light_mod->load_texture("res/textures/wall.jpg");

	eng->add_model(player_mod);
	eng->add_model(light_mod);

	player->set_model(player_mod);
	eng->add_entity(player);
	eng->set_player(player);
	player->move_to(0.0f, 0.0f, 0.0f);

	memset(state->plat_end, 0, 3 * sizeof(float));
	memset(state->plat_start, 0, 3 * sizeof(float));
	state->next = forw;
	state->rotate = false;
	state->frames = 0;
	create_platform(eng, state);

	light->set_model(light_mod);
	eng->add_entity(light);
	eng->add_light_source(light);
	light->scale(0.1f, 0.1f, 0.1f);
	light->move_to(2.0f, 1.1f, 0.0f);
}

int		main(void)
{
	Engine	engine;
	state	state;
	
	srand(time(NULL));
	engine.init_engine(WIDTH, HEIGHT);
	engine.state = &state;
	init_game(&engine, &state);
	engine.run_engine(game_loop);
	return 0;
}
