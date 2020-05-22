#include <iostream>
#include <cmath>

#include "../include/SDL2_image/include/SDL_image.h"

#include "GameObject.h"
#include "Camera.h"
#include "Map.h"


Map::Map()
{
}

Map::~Map()
{
	delete instance;
}

Map* Map::instance = nullptr;

Map* Map::Instance()
{
	if (instance == nullptr)
	{
		instance = new Map();
	}
	
	return instance;
}

void Map::init(int width, int heigth)
{
	map.resize(heigth / objectSize);

	for (auto& it : map)
	{
		it.resize(width / objectSize);
	}

	grassStartPixel = (3 * (int)map.size()) / 4;

	for (int i = 0; i < grassStartPixel; i++)
	{
		for (auto& it : map[i])
		{
			it = MapObjectType::Sky;
		}
	}

	for (int i = grassStartPixel; i < map.size(); i++)
	{
		for (auto& it : map[i])
		{
			it = MapObjectType::Grass;
		}
	}
	map[11][0] = MapObjectType::Grass;
	map[10][0] = MapObjectType::Grass;
	map[12][1] = MapObjectType::Grass;
	map[13][2] = MapObjectType::Grass;
	map[11][12] = MapObjectType::Grass;
	map[12][15] = MapObjectType::Grass;
	map[11][14] = MapObjectType::Grass;
	map[12][24] = MapObjectType::Grass;
	map[14][12] = MapObjectType::Grass;

	map[14][3] = MapObjectType::Grass;
	map[14][5] = MapObjectType::Grass;

	map[15][12] = MapObjectType::Sky;
	map[15][13] = MapObjectType::Sky;
	map[15][14] = MapObjectType::Sky;
	map[15][15] = MapObjectType::Sky;

	map[16][12] = MapObjectType::Sky;
	map[16][13] = MapObjectType::Sky;
	map[16][14] = MapObjectType::Sky;
	map[16][15] = MapObjectType::Sky;

	grassStartPixel *= objectSize;
}

int Map::getObjectSize()
{
	return objectSize;
}

int Map::getMapHeigth()
{
	return objectSize * (int)map.size();
}

int Map::getMapWidth()
{
	return map[0].size() * objectSize;
}

int Map::getGrassStartPixel()
{
	return grassStartPixel;
}

void Map::Draw(SDL_Renderer* ren)
{
	SDL_Surface* sur = IMG_Load("../assets/pictures/sky.png");
	static SDL_Texture * sky = SDL_CreateTextureFromSurface(ren, sur);
	SDL_FreeSurface(sur);
	
	sur = IMG_Load("../assets/pictures/grass.png");
	static SDL_Texture *grass = SDL_CreateTextureFromSurface(ren, sur);
	SDL_FreeSurface(sur);

	SDL_Rect *dest, *src;
	dest = new SDL_Rect();
	src = new SDL_Rect();
	dest->h = dest->w = objectSize;
	src->w = src->h = objectSize;

	dest->y = dest->x = 0;

	SDL_Rect* camera = Camera::Instance()->getCameraRect();

	int xParts = (camera->x + camera->w) / objectSize;

	if (((camera->x + camera->w) % objectSize) > 0)
	{
		xParts++;
	}

	int startingX = (camera->x % objectSize) * -1;

	for (int i = camera->y / objectSize; i < (camera->y + camera->h) / objectSize; i++)
	{
		dest->x = startingX;
		for (int j = camera->x / objectSize; j < xParts; j++)
		{	
			switch (map[i][j])
			{
			case MapObjectType::Sky:
			{
				SDL_RenderCopy(ren, sky, src, dest);
				break;
			}
			case MapObjectType::Grass:
			{
				SDL_RenderCopy(ren, grass, src, dest);
				break;
			}
			default:
				break;
			}
			dest->x += objectSize;
		}
		dest->y += objectSize;
	}

	/*
	for (int i = 0; i < map.size(); i++)
	{
		dest->y = i * objectSize;
		for (int j = 0; j < map[i].size(); j++)
		{
			dest->x = j * objectSize;
			switch (map[i][j])
			{
			case MapObjectType::Sky:
			{
				SDL_RenderCopy(ren, sky, src, dest);
				break;
			}
			case MapObjectType::Grass:
			{
				SDL_RenderCopy(ren, grass, src, dest);
				break;
			}
			default:
				break;
			}
		}
	}
	*/
}

bool Map::Collision(GameObject* gameObject, Direction direction, double distance, double &offset)
{
	unsigned int heightParts = gameObject->getHeigthPartsCount();
	unsigned int widthParts = gameObject->getWidthPartsCount();

	double x = gameObject->getX();
	double y = gameObject->getY();

	switch (direction)
	{
	case(Direction::Up):
	{
		y -= distance;
		break;
	}
	case(Direction::Down):
	{
		y += distance;
		break;
	}
	case(Direction::Left):
	{
		x -= distance;
		break;
	}
	case(Direction::Right):
	{
		x += distance;
		break;
	}
	default: break;
	}

	int xPartTemp = x / objectSize;
	int yPartTemp = y / objectSize;

	int xPartsCount = ceil((x + objectSize * widthParts) / objectSize);

	if ((xPartsCount - xPartTemp) > widthParts) xPartsCount = widthParts + 1;
	else xPartsCount = widthParts;

	int yPartsCount = ceil((y + objectSize * heightParts) / objectSize);

	if ((yPartsCount - yPartTemp) > heightParts) yPartsCount = heightParts + 1;
	else yPartsCount = heightParts;

	for (int i = 0; i < yPartsCount; i++)
	{
		for (int j = 0; j < xPartsCount; j++)
		{
			if (map[yPartTemp + i][xPartTemp + j] != MapObjectType::Sky)
			{
				//std::cout << "Check: " << yPartTemp + i << ", " << xPartTemp + j << std::endl;
				switch (direction)
				{
				case(Direction::Up):
				{
					offset = gameObject->getY() - (yPartTemp + i + 1) * objectSize;
					break;
				}
				case(Direction::Down):
				{
					offset = (yPartTemp + i) * objectSize - (gameObject->getY() + gameObject->getHeigthPartsCount() * objectSize);
					break;
				}
				case(Direction::Left):
				{
					offset = (xPartTemp + j + 1) * objectSize - gameObject->getX();
					break;
				}
				case(Direction::Right):
				{
					offset = (xPartTemp + j) * objectSize - (gameObject->getX() + widthParts * objectSize);
					break;
				}
				}

				return true;
			}
		}
	}
	return false;
}