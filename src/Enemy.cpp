#include "Enemy.h"

Enemy::Enemy() : GameObject()
{

}

Enemy::Enemy(const Enemy& enemy)
{

}

Enemy::Enemy(const tinyxml2::XMLElement *, SDL_Renderer *)
{

}

Enemy::Enemy(std::string &textureSheet, SDL_Renderer* ren, Cordinates cords, unsigned int heigthPartsCount, unsigned int widthPartsCount)
	: GameObject(textureSheet, ren, cords, heigthPartsCount, widthPartsCount)
{
	setTag(GameObjectTag::Enemy);
}

Enemy::~Enemy()
{
	
}

void Enemy::Move()
{

}

bool Enemy::InRange(const SDL_Rect *)
{
	return false;
}
