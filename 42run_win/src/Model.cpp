#include <iostream>
#include "Model.h"
#include "glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Model::LoadMesh()
{
	vert_number = 4;
	float default_vert[32] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f
	};
	vertices = new float[32];
	for (int i = 0; i < 32; ++i)
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
	glBufferData(GL_ARRAY_BUFFER, 8 * vert_number * sizeof(float), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_number * sizeof(float), indices, GL_STATIC_DRAW);
	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Model:: LoadTexture()
{
	int nrChannels;

	text_data = stbi_load("res/textures/wall.jpg", &text_width, &text_height, &nrChannels, 0);
	if (!text_data)
		std::cout << "can't load texture file" << std::endl;
}

void Model::BindTexture()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, text_width, text_height, 0, GL_RGB, GL_UNSIGNED_BYTE, text_data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(text_data);
}
