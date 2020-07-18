#pragma once

#include "../include/SDL2/include/SDL.h"
#include "../include/SDL2_image/include/SDL_image.h"

#include "Player.h"
#include "BadTurtle.h"

struct SDLWindowDestroyer
{
	void operator()(SDL_Window* w) const
	{
		SDL_DestroyWindow(w);
	}
};

class Game
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning = false;
public:
	Game();
	~Game();

	void init(const char* title, int x, int y, int width, int height, bool fullscreen);
	void handleEvent();
	void update();
	void render();
	void clean();
	inline bool running() { return isRunning; }
};