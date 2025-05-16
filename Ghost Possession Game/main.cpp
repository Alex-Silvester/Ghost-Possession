
#include "src/Game.h"

int main()
{
	Game& game = Game::get();

	if (!game.init())
	{
		printf("[ERROR] Game failed to initialise...\n");
		game.end();
		getchar();
		return -1;
	}
	printf("[SUCCESS] Game initialised!\n");

	game.run();

	game.end();

	return 0;
}