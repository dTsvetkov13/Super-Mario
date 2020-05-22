#pragma once

#include <vector>
#include "SDL.h"
#include "Enums.h"
#include "GameObject.h"

class Map
{
private:
	Map();
	Map(Map const& map);
	std::vector<std::vector<MapObjectType>> map;
	static Map* instance;
	const int objectSize = 32;
	int grassStartPixel = 0;
public:
	~Map();

	static Map* Instance();
	void init(int width, int heigth);
	int getObjectSize();
	int getMapHeigth();
	int getMapWidth();
	int getGrassStartPixel();
	void Draw(SDL_Renderer* ren);
	bool Collision(GameObject*, Direction, double distance, double &offset);
};