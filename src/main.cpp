#include <iostream>
#include "../include/SDL2/include/SDL.h"
#include "../include/SDL2_image/include/SDL_image.h"
#include "../include/SDL2_ttf/include/SDL_ttf.h"
#include "Game.h"

Game* game = nullptr;

int main(int argc, char** argv)
{
	game = new Game();

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	IMG_Init(IMG_INIT_PNG);
	IMG_Init(IMG_INIT_JPG);
	TTF_Init();

	SDL_StartTextInput();

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvent();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	SDL_StopTextInput();
	game->clean();

	system("pause");

	return 0;
}