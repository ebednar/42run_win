#include "42run.h"

void replace_light(Engine* eng)
{
	if (eng->state->next == forw)
		eng->state->prev_light->move_to(eng->state->plat_start[0] + 15.0f, 2.0f, eng->state->plat_start[2]);
	else if (eng->state->next == right)
		eng->state->prev_light->move_to(eng->state->plat_start[0], 2.0f, eng->state->plat_start[2] + 15.0f);
	else if (eng->state->next == left)
		eng->state->prev_light->move_to(eng->state->plat_start[0], 2.0f, eng->state->plat_start[2] - 15.0f);
	Entity* ptr = eng->state->prev_light;
	eng->state->prev_light = eng->state->current_light;
	eng->state->current_light = eng->state->next_light;
	eng->state->next_light = ptr;
}

void rand_next_platform(Engine *eng)
{
	int next = rand() % 3;
	if (next == 1 && eng->state->next != left)
		eng->state->next = right;
	else if (next == 2 && eng->state->next != right)
		eng->state->next = left;
	else
		eng->state->next = forw;
	eng->state->plat_start[0] = eng->state->plat_end[0];
	eng->state->plat_start[2] = eng->state->plat_end[2];
}

void	replace_obst(Engine* eng)
{
	int raw;
	int line = 6;

	for (int i = 0; i < 6; ++i)
	{
		raw = rand() % 3 - 1;
		line += rand() % 3 + 1;
		if (eng->state->next == forw)
			eng->state->obst1[i]->move_to(eng->state->plat_end[0] + line, -0.5f, eng->state->plat_end[2] + raw);
		else if (eng->state->next == right)
			eng->state->obst1[i]->move_to(eng->state->plat_end[0] + raw, -0.5f, eng->state->plat_end[2] + line);
		else
			eng->state->obst1[i]->move_to(eng->state->plat_end[0] + raw, -0.5f, eng->state->plat_end[2] - line);
	}
	Entity** ptr = eng->state->obst1;
	eng->state->obst1 = eng->state->obst2;
	eng->state->obst2 = ptr;
}

void	replace_coins(Engine* eng)
{
	int raw;
	int line = 6;

	for (int i = 0; i < 6; ++i)
	{
		raw = rand() % 3 - 1;
		line += rand() % 3 + 1;
		if (eng->state->next == forw)
			eng->state->coins1[i]->move_to(eng->state->plat_end[0] + line, -0.5f, eng->state->plat_end[2] + raw);
		else if (eng->state->next == right)
			eng->state->coins1[i]->move_to(eng->state->plat_end[0] + raw, -0.5f, eng->state->plat_end[2] + line);
		else
			eng->state->coins1[i]->move_to(eng->state->plat_end[0] + raw, -0.5f, eng->state->plat_end[2] - line);
		for (int j = 0; j < 6; ++j)
		{
			if (eng->state->coins1[i]->position == eng->state->obst2[j]->position)
				eng->state->coins1[i]->move(0.0f, 1.2f, 0.0f);
		}
	}
	Entity** ptr = eng->state->coins1;
	eng->state->coins1 = eng->state->coins2;
	eng->state->coins2 = ptr;
}

void replace_platform(Engine *eng)
{
	int				i;
	int				j;
	unsigned int	k;
	Entity** ptr;

	k = 0;
	replace_obst(eng);
	replace_coins(eng);
	if (eng->state->next == forw)
	{
		for (i = -1; i < 29; ++i)
			for (j = -1; j < 2; ++j)
				eng->state->current_plat[k++]->move_to((float)i + eng->state->plat_end[0], -1.05f, (float)j + eng->state->plat_end[2]);
		eng->state->plat_end[0] += 29.0f;
	}
	else if (eng->state->next == right)
	{
		for (i = -1; i < 29; ++i)
			for (j = -1; j < 2; ++j)
				eng->state->current_plat[k++]->move_to((float)j + eng->state->plat_end[0], -1.05f, (float)i + eng->state->plat_end[2]);
		eng->state->plat_end[2] += 29.0f;
	}
	else
	{
		for (i = -1; i < 29; ++i)
			for (j = -1; j < 2; ++j)
				eng->state->current_plat[k++]->move_to((float)j + eng->state->plat_end[0], -1.05f, eng->state->plat_end[2] - (float)i);
		eng->state->plat_end[2] -= 29.0f;
	}
	ptr = eng->state->current_plat;
	eng->state->current_plat = eng->state->next_plat;
	eng->state->next_plat = ptr;
}

void	rotate_player(Engine* eng)
{
	float speed;

	speed = 90.0f * eng->delta_time;
	eng->state->frames += speed;
	if (eng->state->current == right)
	{
		eng->player->rotate(0.0f, -speed, 0.0f);
	}
	else if (eng->state->current == left)
	{
		eng->player->rotate(0.0f, speed, 0.0f);
	}
	if (abs(eng->state->frames) >= 90.0f)
	{
		eng->state->frames = 0.0f;
		eng->state->rotate = false;
		eng->state->shift_rotate = false;
		if (eng->state->w_current == right)
		{
			eng->player->angle.y = -90.0f;
		}
		if (eng->state->w_current == forw)
		{
			eng->player->angle.y = 0.0f;
		}
		if (eng->state->w_current == left)
		{
			eng->player->angle.y = 90.0f;
		}
		if (eng->state->w_current == right && eng->state->next == forw)
			eng->state->current = left;
		else if (eng->state->w_current == left && eng->state->next == forw)
			eng->state->current = right;
		else if (eng->state->w_current == eng->state->next)
			eng->state->current = forw;
		else
			eng->state->current = eng->state->next;
		eng->state->w_current = eng->state->next;
	}
}

void	game_loop(Engine* eng)
{
	controls(eng);
	for (int i = 0; i < 6; ++i)
	{
		eng->state->coins1[i]->rotate(0.0f, 90.0f * eng->delta_time, 0.0f);
		eng->state->coins2[i]->rotate(0.0f, 90.0f * eng->delta_time, 0.0f);
	}
	if (eng->state->rotate)
	{
		rotate_player(eng);
		return;
	}
	if (eng->state->delay >= 0)
	{
		eng->state->delay--;
		if (eng->state->delay == 0)
		{
			std::cout << "replace" << std::endl;
			replace_platform(eng);
			replace_light(eng);
		}
	}
	if (abs(eng->player->position.x + eng->player->position.z - eng->state->plat_start[0] - eng->state->plat_start[2]) <= 2.0f)
	{
		std::cout << "detect1 " << eng->state->current << std::endl;
		if (eng->state->current != forw)
		{
			std::cout << "detect2 " << eng->state->current << std::endl;
		}
		eng->state->rotate = true;
		rand_next_platform(eng);
		eng->state->delay = 120;
	}
	else if (abs(eng->player->position.x + eng->player->position.z - eng->state->plat_start[0] - eng->state->plat_start[2]) <= 4.0f)
	{
		if (eng->state->current == forw)
			return ;
		eng->state->shifting = false;
		eng->state->shift_rotate = true;
		if (eng->state->p_pos == left_r)
			shift_player_r(eng);
		else if (eng->state->p_pos == right_r)
			shift_player_l(eng);
		if (eng->state->shift == 0)
		{
			if (eng->state->w_current == forw)
				eng->player->position.x = eng->state->plat_start[0];
			else
				eng->player->position.z = eng->state->plat_start[2];
		}
	}
}
