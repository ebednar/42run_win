#include "Render.h"
#include "glad.h"

void Render::AddModel(Model *mod)
{
	models.push_back(mod);
}

void Render::DrawModels()
{
	for (Model* mod : models)
	{
		glUseProgram(mod->shader_id);
		glBindVertexArray(mod->vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}