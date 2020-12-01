#pragma once
#include "engine.h"

#define WIDTH 1280
#define HEIGHT 720

enum next_dir
{
	forw,
	left,
	right
};

struct state
{
	float		p_new_pos[3];
	float		plat_end[3];
	float		plat_start[3];
	Entity		**current_plat;
	Entity		**next_plat;
	bool		rotate;
	int			frames;
	next_dir	current;
	next_dir	next;
};