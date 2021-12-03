#include <iostream>
#include "Game.h"

int main() {

	std::srand(static_cast<unsigned>(time(NULL)));

	Game game;

	/* Game Loop */
	while (game.isRunning() && !game.isGameEnded()) {
		game.update();
		game.render();
	}

	return 0;
}