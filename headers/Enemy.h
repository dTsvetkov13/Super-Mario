#pragma once

#include <iostream>
#include "GameObject.h"

class Enemy : public GameObject
{
private:

public:
	Enemy();
	Enemy(const Enemy&);
	Enemy(const tinyxml2::XMLElement*, SDL_Renderer*);
	Enemy(std::string &textureSheet, SDL_Renderer* ren, Cordinates cords, unsigned int heigthPartsCount, unsigned int widthPartsCount);
	virtual ~Enemy();
	virtual void Move();
	virtual bool InRange(const SDL_Rect*);
};