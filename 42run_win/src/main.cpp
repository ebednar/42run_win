#include "42run.h"
#include <time.h>
#include "irrKlang.h"

int		main(void)
{
	Engine	engine;
	state	state;
	
	srand(time(NULL));
	engine.init_engine(WIDTH, HEIGHT);
	engine.state = &state;
	init_game(&engine, &state);
	irrklang::ISoundEngine* sound_engine = irrklang::createIrrKlangDevice();
	//sound_engine->play2D("", true);
	engine.run_engine(game_loop);
	delete(engine.state->current_plat);
	delete(engine.state->next_plat);
	delete(engine.state->obst1);
	delete(engine.state->obst2);
	return 0;
}
