#pragma once

#include "Enemy.h"

class SeverusSnape :
	public Enemy
{
private:
	int rangeInPixels = 200;
	bool inRange = false;

	void SayAPhrase(std::string&, SDL_Renderer*);
public:
	SeverusSnape();
	SeverusSnape(std::string &textureSheet, SDL_Renderer* ren, int startX, unsigned int heigthPartsCount, unsigned int widthPartsCount, double startsAt);
	~SeverusSnape();

	bool InRange(const SDL_Rect*) override;

	void Update() override;
	void Render(SDL_Renderer*) override;
};