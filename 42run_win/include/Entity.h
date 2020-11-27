#pragma once
#include "Model.h"

class Entity
{
public:
	Model	*mod;
	float	position[3];
	float	e_scale[3];
	float	angle[3];
public:
	Entity();
	void set_model(const char *path);
	void move(float x, float y, float z);
	void move_to(float x, float y, float z);
	void rotate(float x, float y, float z);
	void scale(float x, float y, float z);
private:
};
