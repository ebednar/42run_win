#pragma once
#include "entity.h"
#include <vector>
#include "camera.h"
#include "ui_text.h"
struct vec3
{
	float x;
	float y;
	float z;
};

class Render
{
public:
	Entity *player;
public:
	void	init();
	void	set_lights_pos(glm::vec3 **lights, int numb);
	void	draw_scene(std::vector<Entity *> scene, glm::vec3** lights, Camera *cam, bool free_cam);
	void	draw_ui(ui_text* Texter, std::vector<text_t*> text);
private:
	glm::mat4	projection;
	glm::mat4	ortProjection;
	vec3		light_pos[3];
};
