#pragma once

#define WIDTH 640
#define HEIGHT 480

enum next_plat
{
	forw,
	left,
	right
};

struct state
{
	float p_old_pos[3];
	float plat_end[3];
	next_plat next;
};