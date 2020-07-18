#include <iostream>
#include "../include/SDL2/include/SDL.h"
#include "../include/SDL2_ttf/include/SDL_ttf.h"
#include "Game.h"
#include "GameObject.h"
#include <string>
#include "Map.h"
#include "World.h"
#include "Camera.h"
#include "SeverusSnape.h"
#include "Database.h"

Game::Game()
{
}


Game::~Game()
{
	delete renderer;
	delete window;
}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Initilize\n";

		window = SDL_CreateWindow(title, x, y, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);

		SDL_SetWindowTitle(window, "Super Mario");

		int x1, y1;

		SDL_GetWindowPosition(window, &x1, &y1);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			Map::Instance()->init(width * 2, height, 480);
			std::string playerPng = "../assets/pictures/super-mario-run -2.png";
			std::string badTurtleJpg = "../assets/pictures/bad-turtle.jpg";
			std::string severusSnapePng = "../assets/pictures/severus-snape.png";

			std::unique_ptr<Enemy> d;
			std::unique_ptr<Player> player = std::make_unique<Player>(playerPng, renderer,
				Cordinates(Map::Instance()->getObjectSize() * 3, (Map::Instance()->getGrassStartPixel()
					- Map::Instance()->getObjectSize()) - Map::Instance()->getObjectSize() * 2)
				, 2, 2);
			d = std::make_unique<BadTurtle>(badTurtleJpg, renderer, Cordinates(530, Map::Instance()->getGrassStartPixel() - Map::Instance()->getObjectSize()), 1, 1, 530);
			
			World::Instance()->setPlayer(player);
			//World::Instance()->addEnemy(d);

			d = std::make_unique<BadTurtle>(badTurtleJpg, renderer, Cordinates(210, Map::Instance()->getGrassStartPixel() - Map::Instance()->getObjectSize()), 1, 1, 220);

			//World::Instance()->addEnemy(d);

			d = std::make_unique<SeverusSnape>(severusSnapePng, renderer, Cordinates(1450, Map::Instance()->getGrassStartPixel() - 4 * Map::Instance()->getObjectSize()), 4, 2);

			World::Instance()->addEnemy(d);

			Camera::Instance()->init(0, 0, height, width);
			Camera::Instance()->setWindowRect(x1, y1, height, width);

			Database::Instance();
			Database::Instance()->LoadGameObjects(renderer);
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
}

void Game::handleEvent()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		World::Instance()->PlayerHandleEvent(event);
		break;
	}
}

void Game::update()
{
	if (World::Instance()->GetPlayerDied())
	{
		isRunning = false;
		return;
	}

	World::Instance()->Update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	Map::Instance()->Draw(renderer);
	World::Instance()->Render(renderer);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}