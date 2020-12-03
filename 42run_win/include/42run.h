#pragma once
#include "engine.h"
#include <iostream>

#define WIDTH 640
#define HEIGHT 480

enum next_dir
{
	forw,
	left,
	right
};

enum player_pos
{
	left_r,
	center_r,
	right_r
};

struct state
{
	float		plat_end[3];
	float		plat_start[3];
	Entity		**current_plat;
	Entity		**next_plat;
	bool		rotate;
	float		frames;
	next_dir	current;
	next_dir	w_current;
	next_dir	next;
	next_dir	p_pos;
	float		shifting_x;
	float		shifting_y;
	bool		shifting;
};

void	init_game(Engine* eng, state* state);
void	game_loop(Engine* eng);
void	controls(Engine* eng);
