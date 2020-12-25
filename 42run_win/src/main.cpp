#include "42run.h"
#include <time.h>
#include "irrKlang.h"

int		main(int argc, char **argv)
{
	Engine	engine;
	state	state;
	
	srand(time(NULL));
	engine.init_engine(WIDTH, HEIGHT);
	engine.state = &state;
	if (argc == 2 && argv[1] == "-f")
		engine.free_cam = true;
	init_game(&engine, &state);
	irrklang::ISoundEngine* sound_engine = irrklang::createIrrKlangDevice();
	sound_engine->setSoundVolume(0.1);
	sound_engine->play2D("res/music/Day.mp3", true);
	engine.run_engine(game_loop);
	delete(engine.state->current_plat);
	delete(engine.state->next_plat);
	delete(engine.state->obst1);
	delete(engine.state->obst2);
	return 0;
}
