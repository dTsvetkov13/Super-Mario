#pragma once
#include "Enemy.h"
#include "../include/SDL2/include/SDL.h"

class BadTurtle :
	public Enemy
{
private:
	double speed = 1;
	Direction direction;
	double leftEdge;
	double rightEdge;

public:
	BadTurtle();
	BadTurtle(const BadTurtle&);
	BadTurtle(const tinyxml2::XMLElement*, SDL_Renderer*);
	BadTurtle(std::string &textureSheet, SDL_Renderer* ren, Cordinates cords,
		unsigned int heigthPartsCount, unsigned int widthPartsCount, double leftEdge);
	~BadTurtle();
	
	void init(std::string &textureSheet, SDL_Renderer* ren, Cordinates cords,
		unsigned int heigthPartsCount, unsigned int widthPartsCount, double leftEdge);
	void Update() override;
	void Move() override;
	const CollisionType getCollisionTypeWith(const Direction&, bool) override;
};