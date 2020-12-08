#include "42run.h"

static void	rand_next_platform(Engine *eng)
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

void		rotate_player(Engine* eng)
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

void		game_loop(Engine* eng)
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
			replace_platform(eng);
			replace_light(eng);
		}
	}
	if (abs(eng->player->position.x + eng->player->position.z - eng->state->plat_start[0] - eng->state->plat_start[2]) <= 2.0f)
	{
		eng->state->rotate = true;
		rand_next_platform(eng);
		eng->state->delay = 120;
	}
	else if (abs(eng->player->position.x + eng->player->position.z - eng->state->plat_start[0] - eng->state->plat_start[2]) <= 4.0f)
	{
		if (eng->state->current == forw)
			return;
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
	else (detect_collision(eng));
}
