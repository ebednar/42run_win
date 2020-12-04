#include "render.h"
#include "glad.h"
#include <iostream>

void Render::draw_scene(std::vector<Entity *> scene, std::vector<glm::vec3 *> lights, Camera *cam, bool free_cam)
{
	int length = scene.size();
	if (free_cam)
		cam->update_free();
	else
		cam->update_follow(player->position);
	for (int i = 0; i < length; ++i)
	{
		Entity	*ent = scene[i];
		Model	*mod = ent->mod;
		glUseProgram(mod->shader_id);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mod->texture);
		glBindVertexArray(mod->vao);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, ent->position);
		model = glm::rotate(model, glm::radians(ent->angle[0]), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(ent->angle[1]), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(ent->angle[2]), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, ent->e_scale);

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(60.0f), 640.0f / 480.0f, 0.1f, 100.0f);


		unsigned int model_loc = glGetUniformLocation(mod->shader_id, "u_M");
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
		unsigned int view_loc = glGetUniformLocation(mod->shader_id, "u_V");
		glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(cam->view));
		unsigned int proj_loc = glGetUniformLocation(mod->shader_id, "u_P");
		glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));

		//glUniform3f(glGetUniformLocation(mod->shader_id, "lightPos"), lights[0]->position.x, lights[0]->position.y, lights[0]->position.z);
		glUniform1i(glGetUniformLocation(mod->shader_id, "lightNumb"), 2);
		glUniform3fv(glGetUniformLocation(mod->shader_id, "lightPos"), 2, (GLfloat *)lights[0]);
		glUniform3f(glGetUniformLocation(mod->shader_id, "viewPos"), cam->pos.x, cam->pos.y, cam->pos.z);
		glUniform1i(glGetUniformLocation(mod->shader_id, "material.diffuse"), 0);
		glUniform3f(glGetUniformLocation(mod->shader_id, "material.specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(mod->shader_id, "material.shininess"), 16.0f);
		glUniform3f(glGetUniformLocation(mod->shader_id, "light.ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(mod->shader_id, "light.diffuse"), 0.7f, 0.7f, 0.7f);
		glUniform3f(glGetUniformLocation(mod->shader_id, "light.specular"), 0.7f, 0.7f, 0.7f);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
