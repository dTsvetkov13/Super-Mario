#pragma once

#include <iostream>
#include "GameObject.h"

class Enemy : public GameObject
{
private:

public:
	Enemy();
	Enemy(const Enemy&);
	Enemy(std::string &textureSheet, SDL_Renderer* ren, int startX, unsigned int heigthPartsCount, unsigned int widthPartsCount, double startsAt);
	virtual ~Enemy();
	virtual void Move();
	virtual bool InRange(const SDL_Rect*);
};