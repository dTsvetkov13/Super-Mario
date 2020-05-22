#include "Enemy.h"

Enemy::Enemy() : GameObject()
{

}

Enemy::Enemy(const Enemy& enemy)
{

}

Enemy::Enemy(std::string &textureSheet, SDL_Renderer* ren, int startX, unsigned int heigthPartsCount, unsigned int widthPartsCount, double startsAt)
	: GameObject(textureSheet, ren, startX, heigthPartsCount, widthPartsCount, startsAt)
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
