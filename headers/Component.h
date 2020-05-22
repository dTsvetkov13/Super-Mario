#pragma once
#include "SDL.h"
#include "Enums.h"

class Component
{
private:
	ComponentType type;
public:
	Component();
	inline ComponentType getType() { return type; }
	virtual void Draw(SDL_Renderer* ren) = 0;
	virtual void Update() = 0;

	virtual ~Component() = 0;
};