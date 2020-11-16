#include "Model.h"
#include "glad.h"

Model::Model()
{

}

void Model::LoadMesh()
{
	vert_number = 4;
	float default_vert[12] = {
	-0.9f, -0.9f, 0.0f,
	-0.9f,  0.9f, 0.0f,
	 0.9f,  0.9f, 0.0f,
	 0.9f, -0.9f, 0.0f
	};
	vertices = new float[12];
	for (int i = 0; i < 12; ++i)
		vertices[i] = default_vert[i];
	ind_number = 6;
	indices = new unsigned int[6];
	unsigned int default_indices[6] = {
		0, 1, 2,
		0, 2, 3
	};
	for (int i = 0; i < 6; ++i)
		indices[i] = default_indices[i];
}

void Model::VertexBuffer()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * vert_number * sizeof(float), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_number * sizeof(float), indices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}