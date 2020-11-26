#include "Entity.h"

Entity::Entity()
{
	move_to(0.0f, 0.0f, 0.0f);
	angle[0] = 0;
	angle[1] = 0;
	angle[2] = 0;
	scale(1.0f, 1.0f, 1.0f);

}

void Entity::set_model()
{
	mod = new Model();

	mod->load_mesh();
	mod->vertex_buffer();
	mod->set_shader("res/shaders/vertex.shader", "res/shaders/fragment.shader");
	mod->load_texture("res/textures/wall.jpg");
	mod->bind_texture();
}

void Entity::move(float x, float y, float z)
{
	position[0] += x;
	position[1] += y;
	position[2] += z;
}

void Entity::move_to(float x, float y, float z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

void Entity::rotate(float x, float y, float z)
{
	angle[0] += x;
	angle[1] += y;
	angle[2] += z;
}

void Entity::scale(float x, float y, float z)
{
	e_scale[0] = x;
	e_scale[1] = y;
	e_scale[2] = z;
}
