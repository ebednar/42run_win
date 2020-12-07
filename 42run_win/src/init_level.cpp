#include "42run.h"

void	generate_obst(Engine* eng, Entity** obst)
{
	int raw;
	int line = 6;

	for (int i = 0; i < 6; ++i)
	{
		raw = rand() % 3 - 1;
		line += rand() % 3 + 1;
		obst[i]->move_to(eng->state->plat_end[0] + line, -0.5f, eng->state->plat_end[2] + raw);
	}
}

void	generate_coins(Engine* eng, Entity** coins)
{
	int raw;
	int line = 6;

	for (int i = 0; i < 6; ++i)
	{
		raw = rand() % 3 - 1;
		line += rand() % 3 + 1;
		coins[i]->scale(0.2f, 0.2f, 0.2f);
		coins[i]->move_to(eng->state->plat_end[0] + line, -0.5f, eng->state->plat_end[2] + raw);
		for (int j = 0; j < 6; ++j)
		{
			if (coins[i]->position == eng->state->obst2[j]->position)
				coins[i]->move(0.0f, 1.2f, 0.0f);
		}
	}
}

static void	create_platform(Engine* eng, state* state)
{
	Model			*platform_mod = new Model();
	int				i;
	int				j;
	unsigned int	k;

	platform_mod->load_obj("res/models/platform.obj", true);
	platform_mod->set_shader("res/shaders/stand_vertex.glsl", "res/shaders/stand_fragment.glsl");
	platform_mod->load_texture("res/textures/wall.jpg");
	eng->add_model(platform_mod);
	state->current_plat = new Entity*[30 * 3];
	state->next_plat = new Entity*[30 * 3];
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
	generate_obst(eng, state->obst1);
	generate_coins(eng, state->coins1);
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
	generate_obst(eng, state->obst2);
	generate_coins(eng, state->coins2);
	state->plat_end[0] += 29.0f;
	eng->state->w_current = forw;
}

void		create_obst(Engine* eng)
{
	Model* mod = new Model();

	mod->load_obj("res/models/test.obj", true);
	mod->set_shader("res/shaders/stand_vertex.glsl", "res/shaders/stand_fragment.glsl");
	mod->load_texture("res/textures/wall.jpg");

	for (int i = 0; i < 6; ++i)
	{
		Entity* obst = new Entity;
		obst->set_model(mod);
		eng->add_entity(obst);
		eng->state->obst1[i] = obst;
	}
	for (int i = 0; i < 6; ++i)
	{
		Entity* obst = new Entity;
		obst->set_model(mod);
		eng->add_entity(obst);
		eng->state->obst2[i] = obst;
	}
}

void		create_coins(Engine* eng)
{
	Model* mod = new Model();

	mod->load_obj("res/models/coin.obj", true);
	mod->set_shader("res/shaders/coin_vertex.glsl", "res/shaders/coin_fragment.glsl");
	mod->load_texture("res/textures/wall.jpg");

	for (int i = 0; i < 6; ++i)
	{
		Entity* coin = new Entity;
		coin->set_model(mod);
		eng->add_entity(coin);
		eng->state->coins1[i] = coin;
	}
	for (int i = 0; i < 6; ++i)
	{
		Entity* coin = new Entity;
		coin->set_model(mod);
		eng->add_entity(coin);
		eng->state->coins2[i] = coin;
	}
}

void		init_game(Engine* eng, state* state)
{
	Entity* player = new Entity();
	Entity* light1 = new Entity();
	Entity* light2 = new Entity();
	Entity* light3 = new Entity();

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
	player->move_to(0.0f, -0.5f, 0.0f);
	player->scale(1.0f, 1.0f, 1.0f);

	memset(state->plat_end, 0, 3 * sizeof(float));
	memset(state->plat_start, 0, 3 * sizeof(float));
	state->next = forw;
	state->current = forw;
	state->rotate = false;
	state->frames = 0.0f;
	state->p_pos = center_r;
	state->shifting_x = 0.0f;
	state->shifting_y = 0.0f;
	eng->state->shifting = true;
	eng->state->shift_rotate = false;
	eng->state->delay = -1;
	eng->state->jump = false;
	eng->state->jump_time = 0;

	light1->set_model(light_mod);
	eng->add_entity(light1);
	eng->add_light_source(light1);
	light1->scale(0.1f, 0.1f, 0.1f);
	light1->move_to(15.0f, 2.0f, 0.0f);

	light2->set_model(light_mod);
	eng->add_entity(light2);
	eng->add_light_source(light2);
	light2->scale(0.1f, 0.1f, 0.1f);
	light2->move_to(45.0f, 2.0f, 0.0f);

	light3->set_model(light_mod);
	eng->add_entity(light3);
	eng->add_light_source(light3);
	light3->scale(0.1f, 0.1f, 0.1f);
	light3->move_to(-15.0f, 2.0f, 0.0f);

	eng->set_lights_pos();
	state->prev_light = light3;
	state->current_light = light1;
	state->next_light = light2;

	state->obst1 = new Entity * [6];
	state->obst2 = new Entity * [6];
	state->coins1 = new Entity * [6];
	state->coins2 = new Entity * [6];
	create_obst(eng);
	create_coins(eng);
	create_platform(eng, state);

	eng->free_cam = false;
}