#pragma once
#include "Model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity
{
public:
	Model	*mod;
	float	position[3];
	float	e_scale[3];
	float	angle[3];
public:
	Entity();
	void set_model();
	void move(float x, float y, float z);
	void move_to(float x, float y, float z);
	void rotate(float x, float y, float z);
	void scale(float x, float y, float z);
private:
};
