#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "render.h"
#include "events.h"

struct state;

class Engine {
public:
	Camera					cam;
	double					delta_time = 0.0;
	std::vector<Model *>	models;
	std::vector<Entity *>	scene;
	Controls				controls;
	Entity					*player;
	std::vector<Entity *>	light_sources;
	state					*state;
	bool					free_cam;
public:
	~Engine();
	void init_engine(int width, int height);
	void run_engine(void (*func)(Engine *));
	void add_model(Model *mod);
	void add_entity(Entity *ent);
	void set_player(Entity *ent);
	void add_light_source(Entity *ent);
private:
	GLFWwindow				*window;
	Render					rend;
	double					old_time = 0.0;
	double					timer = 0.0;
	int						fps = 0;
};
