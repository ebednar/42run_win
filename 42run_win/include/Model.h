#pragma once

class Model
{
public:
	float			*vertices;
	unsigned int	*indices;
	unsigned char	*text_data;
	int				text_width;
	int				text_height;
	unsigned int	vert_number;
	unsigned int	ind_number;
	unsigned int	vbo;
	unsigned int	vao;
	unsigned int	ibo;
	unsigned int	texture;
	int	shader_id;
public:
	void LoadMesh();
	void SetShader();
	void VertexBuffer();
	void LoadTexture();
	void BindTexture();
private:

};
