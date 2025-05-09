
#include "src/Game.h"

int main()
{
	Game& game = Game::get();

	unsigned int max_fps = 120;

	if (!game.init(max_fps))
	{
		game.end();
		printf("[ERROR] Failed to initialise game...\n");
		auto t = getchar();
		return -1;
	}

	game.run();

	game.end();

	return 0;
}
