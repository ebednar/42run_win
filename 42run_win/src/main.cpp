#include "42run.h"
#include "engine.h"
#include <iostream>

void game_script(Engine *eng)
{
	eng->scene[0]->rotate(360 * eng->delta_time, 0.0f, 0.0f);
}

int main(void)
{
	Engine	engine;
	Entity* ent = new Entity();

	engine.init_engine(WIDTH, HEIGHT);
	
	ent->set_model();
	engine.add_entity(ent);
	
	engine.run_engine(game_script);
	return 0;
}
