#include <iostream>
#include "..\Header Files\Game.h"
int main()
{
	Game game;
	while (game.isRunning())
	{

		game.update();
		game.render();
	}
	return 0;
}
/*

	Please implement the picture of the buttons, textbox and etc soon
*/