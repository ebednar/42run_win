#include "engine.h"
#include "glad.h"
#include <iostream>

Engine::~Engine()
{
	int length = scene.size();
	for (int i = 0; i < length; ++i)
	{
		delete scene[i]->mod->vertices;
		delete scene[i]->mod;
		delete scene[i];
	}
	std::cout << "Engine off" << std::endl;
}

void Engine::init_engine(int width, int height)
{
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, "42 run", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL())
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetWindowUserPointer(window, &controls);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);

	controls.yaw = cam.yaw;
	controls.pitch = cam.pitch;

}

void Engine::add_entity(Entity *ent)
{
	scene.push_back(ent);
}

void Engine::run_engine(void (*func)(Engine *))
{
	old_time = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);

		delta_time = glfwGetTime() - old_time;
		timer += delta_time;
		fps++;
		if (timer >= 1.0)
		{
			timer -= 1.0;
			std::cout << "fps - " << fps << std::endl;
			fps = 0;
		}
		old_time = glfwGetTime();

		func(this);

		rend.draw_scene(scene, &cam);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}
