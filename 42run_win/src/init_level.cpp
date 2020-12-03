#include "42run.h"

static void	create_platform(Engine* eng, state* state)
{
	Model* platform_mod = new Model();
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
	eng->state->w_current = forw;
}

void		init_game(Engine* eng, state* state)
{
	Entity* player = new Entity();
	Entity* light = new Entity();

	Model* player_mod = new Model();
	Model* light_mod = new Model();

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
	state->frames = 0.0f;
	state->p_pos = forw;
	state->shifting_x = 0.0f;
	state->shifting_y = 0.0f;
	create_platform(eng, state);

	light->set_model(light_mod);
	eng->add_entity(light);
	eng->add_light_source(light);
	light->scale(0.1f, 0.1f, 0.1f);
	light->move_to(15.0f, 2.0f, 0.0f);
	
	eng->free_cam = false;
}