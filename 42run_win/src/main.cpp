#include "42run.h"
#include "engine.h"
#include <time.h>
#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void	controls(Engine	*eng)
{
	/*eng->cam.speed = 2.5f * eng->delta_time;
	if (eng->controls.keys[GLFW_KEY_W])
		eng->cam.pos += eng->cam.speed * eng->cam.front;
	if (eng->controls.keys[GLFW_KEY_S])
		eng->cam.pos -= eng->cam.speed * eng->cam.front;
	if (eng->controls.keys[GLFW_KEY_A])
		eng->cam.pos -= eng->cam.speed * glm::normalize(glm::cross(eng->cam.front, eng->cam.up));
	if (eng->controls.keys[GLFW_KEY_D])
		eng->cam.pos += eng->cam.speed * glm::normalize(glm::cross(eng->cam.front, eng->cam.up));
	eng->cam.yaw = eng->controls.yaw;
	eng->cam.pitch = eng->controls.pitch;*/

	float speed = 6.0f * eng->delta_time;
	if (eng->controls.keys[GLFW_KEY_W])
		eng->player->move(speed * cos(glm::radians(eng->player->angle[1])), 0.0f, -speed * sin(glm::radians(eng->player->angle[1])));
	if (eng->controls.keys[GLFW_KEY_S])
		eng->player->move(-speed * cos(glm::radians(eng->player->angle[1])), 0.0f, speed *sin(glm::radians(eng->player->angle[1])));
	if (eng->controls.keys[GLFW_KEY_A])
		eng->player->rotate(0.0f, 20 * speed, 0.0f);
	if (eng->controls.keys[GLFW_KEY_D])
		eng->player->rotate(0.0f, -20 * speed, 0.0f);
	eng->cam.pos.x = eng->player->position[0];
	eng->cam.pos.z = eng->player->position[2];
	eng->cam.yaw = -eng->player->angle.y;
}

void	game_loop(Engine *eng)
{
	//std::cout << eng->state->plat_end[0] << std::endl;
	if (eng->state->plat_end[0] - eng->player->position.x <= 2.0f)
		std::cout << "end" << std::endl;
	controls(eng);
}

void	create_platform(Engine *eng, state* state)
{
	Model	*platform_mod = new Model();
	int		i;
	int		j;

	platform_mod->load_obj("res/models/test.obj");
	platform_mod->set_shader("res/shaders/stand_vertex.glsl", "res/shaders/stand_fragment.glsl");
	platform_mod->load_texture("res/textures/wall.jpg");
	eng->add_model(platform_mod);

	if (state->next == forw)
		for (i = 0; i < 30; ++i)
		{
			for (j = 0; j < 3; ++j)
			{
				Entity* platform = new Entity();
				platform->set_model(platform_mod);
				eng->add_entity(platform);
				platform->scale(1.0f, 0.1f, 1.0f);
				platform->move_to((float)i + state->plat_end[0], -1.05f, (float)j + state->plat_end[2]);
			}
		}
	else
		for (i = 0; i < 30; ++i)
		{
			for (j = 0; j < 3; ++j)
			{
				Entity* platform = new Entity();
				platform->set_model(platform_mod);
				eng->add_entity(platform);
				platform->scale(1.0f, 0.1f, 1.0f);
				platform->move_to((float)j + state->plat_end[0], -1.05f, (float)i + state->plat_end[2]);
			}
		}
	int next = rand() % 3;
	if (next == 0)
	{
		std::cout << "forw" << std::endl;
		state->plat_end[0] += (float)i + state->plat_end[0];
		state->next = forw;
	}
	else
	{
		std::cout << "right" << std::endl;
		state->plat_end[0] += (float)i + state->plat_end[0];
		state->next = right;
	}
}

void	init_game(Engine *eng, state *state)
{
	Entity	*player = new Entity();
	Entity	*light = new Entity();
	
	Model	*player_mod = new Model();
	Model	*light_mod = new Model();

	player_mod->load_obj("res/models/test.obj");
	player_mod->set_shader("res/shaders/stand_vertex.glsl", "res/shaders/stand_fragment.glsl");
	player_mod->load_texture("res/textures/wall.jpg");

	light_mod->load_obj("res/models/test.obj");
	light_mod->set_shader("res/shaders/light_vertex.glsl", "res/shaders/light_fragment.glsl");
	light_mod->load_texture("res/textures/wall.jpg");

	eng->add_model(player_mod);
	eng->add_model(light_mod);

	player->set_model(player_mod);
	eng->add_entity(player);
	eng->set_player(player);
	player->move_to(0.0f, 0.0f, 1.0f);
	state->p_old_pos[0] = player->position.x;
	state->p_old_pos[1] = player->position.y;
	state->p_old_pos[2] = player->position.z;
	memset(state->plat_end, 0, 3 * sizeof(float));
	state->next = forw;

	create_platform(eng, state);
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
