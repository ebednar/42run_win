#include "42run.h"
#include <time.h>

int		main(void)
{
	Engine	engine;
	state	state;
	
	srand(time(NULL));
	engine.init_engine(WIDTH, HEIGHT);
	engine.state = &state;
	init_game(&engine, &state);
	engine.run_engine(game_loop);
	return 0;
}
