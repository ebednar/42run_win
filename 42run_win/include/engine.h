#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Render.h"
#include "Events.h"

class Engine {
public:
	~Engine();
	void init_engine(int width, int height);
	void add_entity(Entity *ent);
	void run_engine(void (*func)(Engine*));
public:
	double delta_time = 0.0;
	std::vector<Entity*> scene;
private:
	GLFWwindow	*window;
	Render rend;
	double old_time = 0.0;
	double timer = 0.0;
	int fps = 0;
};
