#include "Render.h"
#include "glad.h"

void Render::AddEntity(Entity *ent)
{
	scene.push_back(ent);
}

void Render::DrawScene()
{
	int length = scene.size();
	for (int i = 0; i < length; ++i)
	{
		Model *mod = scene[i]->mod;
		glUseProgram(mod->shader_id);
		glBindTexture(GL_TEXTURE_2D, mod->texture);
		glBindVertexArray(mod->vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
