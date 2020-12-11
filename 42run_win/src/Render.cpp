#include "render.h"
#include "glad.h"
#include <string>
#include <iostream>

void Render::init()
{
	projection = glm::perspective(glm::radians(60.0f), 640.0f / 480.0f, 0.1f, 100.0f);
	ortProjection = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f);
}

void Render::set_lights_pos(glm::vec3 **lights, int numb)
{
	for (int i = 0; i < numb; ++i)
	{
		light_pos[i].x = lights[i]->x;
		light_pos[i].y = lights[i]->y;
		light_pos[i].z = lights[i]->z;
	}
}

void Render::draw_scene(std::vector<Entity *> scene, glm::vec3** lights, Camera *cam, bool free_cam)
{
	int length = scene.size();
	if (free_cam)
		cam->update_free();
	else
		cam->update_follow(player->position);
	set_lights_pos(lights, 3);

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

		unsigned int model_loc = glGetUniformLocation(mod->shader_id, "u_M");
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
		unsigned int view_loc = glGetUniformLocation(mod->shader_id, "u_V");
		glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(cam->view));
		unsigned int proj_loc = glGetUniformLocation(mod->shader_id, "u_P");
		glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));

		glUniform1i(glGetUniformLocation(mod->shader_id, "lightNumb"), 3);
		glUniform3fv(glGetUniformLocation(mod->shader_id, "lightPos"), 3, &light_pos[0].x);
		glUniform3f(glGetUniformLocation(mod->shader_id, "viewPos"), cam->pos.x, cam->pos.y, cam->pos.z);
		glUniform1i(glGetUniformLocation(mod->shader_id, "material.diffuse"), 0);
		glUniform3f(glGetUniformLocation(mod->shader_id, "material.specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(mod->shader_id, "material.shininess"), 16.0f);
		glUniform3f(glGetUniformLocation(mod->shader_id, "light.ambient"), 0.3f, 0.3f, 0.3f);
		glUniform3f(glGetUniformLocation(mod->shader_id, "light.diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(mod->shader_id, "light.specular"), 0.5f, 0.5f, 0.5f);
		glUniform1f(glGetUniformLocation(mod->shader_id, "light.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(mod->shader_id, "light.linear"), 0.045f);
		glUniform1f(glGetUniformLocation(mod->shader_id, "light.quadratic"), 0.0075f);
		glDrawArrays(GL_TRIANGLES, 0, mod->ind_number);
	}
}

void Render::draw_ui(ui_text* texter, std::vector<text_t *> text)
{

	
	glUseProgram(texter->shader_id);
	unsigned int proj_loc = glGetUniformLocation(texter->shader_id, "u_P");
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(ortProjection));
	glUniform3f(glGetUniformLocation(texter->shader_id, "textColor"), 1.0f, 1.0f, 1.0f);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(texter->vao);
	int length = text.size();
	for (int i = 0; i < length; ++i)
	{
		text_t* txt = text[i];
		int x = txt->x;
		std::string::const_iterator c;
		for (c = txt->str.begin(); c != txt->str.end(); ++c)
		{
			character ch = texter->characters[*c];
			float xpos = x + ch.bearing.x * txt->scale;
			float ypos = txt->y - (ch.size.y - ch.bearing.y) * txt->scale;

			float w = ch.size.x * txt->scale;
			float h = ch.size.y * txt->scale;

			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
			};
			glBindTexture(GL_TEXTURE_2D, ch.textureID);
			glBindBuffer(GL_ARRAY_BUFFER, texter->vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			x += (ch.advance >> 6) * txt->scale;
		}
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
