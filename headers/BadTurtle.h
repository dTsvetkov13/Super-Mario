#pragma once
#include "Enemy.h"
#include "../include/SDL2/include/SDL.h"

class BadTurtle :
	public Enemy
{
private:
	bool CheckForReceivedDamage();
	double speed = 1;
	Direction direction;
	double leftEdge;
	double rightEdge;

public:
	BadTurtle();
	BadTurtle(const BadTurtle&);
	BadTurtle(std::string &textureSheet, SDL_Renderer* ren, int startX,
		unsigned int heigthPartsCount, unsigned int widthPartsCount,
		double startsAt, double leftEdge);
	~BadTurtle();

	void Update() override;
	void Move() override;
	const CollisionType getCollisionTypeWith(const Direction&, bool) override;
};