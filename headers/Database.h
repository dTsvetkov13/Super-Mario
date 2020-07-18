#pragma once

#include "../include/tinyxml2/tinyxml2.h"
#include "../include/SDL.h"

class Database
{
private:
	static Database* instance;
	tinyxml2::XMLDocument m_doc;

	Database();
	Database(const Database&) {}
public:
	~Database();

	static Database* Instance();

	void LoadGame(SDL_Renderer* ren);
	void LoadMap(SDL_Renderer* ren);
	void LoadGameObjects(SDL_Renderer* ren);
	void LoadCamera(SDL_Renderer* ren);
};

