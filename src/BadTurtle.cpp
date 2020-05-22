#include "../headers/BadTurtle.h"
#include <string>
#include "Map.h"

BadTurtle::BadTurtle() : Enemy()
{
}

BadTurtle::BadTurtle(const BadTurtle&)
{

}

BadTurtle::BadTurtle(std::string &textureSheet, SDL_Renderer* ren, int startX, unsigned int heigthPartsCount, unsigned int widthPartsCount, double startsAt, double leftEdge)
	: Enemy(textureSheet, ren, startX, heigthPartsCount, widthPartsCount, startsAt)
{
	this->leftEdge = leftEdge;
	direction = Direction::Right;
	this->rightEdge = leftEdge + Map::Instance()->getObjectSize() * 2;
}

BadTurtle::~BadTurtle()
{

}

void BadTurtle::Update()
{
	Move();
	/*if (CheckForReceivedDamage())
	{
		std::cout << "RECEIVED DAMAGED" << std::endl;
	}*/
	GameObject::Update();
}

void BadTurtle::Move()
{
	double offset;
	if (Map::Instance()->Collision(this, direction, speed, offset))
	{
		switch (direction)
		{
		case(Direction::Right) :
		{
			incrementX(offset);
			direction = Direction::Left;
			break;
		}
		case(Direction::Left):
		{
			incrementX(-offset);
			direction = Direction::Right;
			break;
		}
		default : break;
		}
		return;
	}
	else
	{
		switch (direction)
		{
		case(Direction::Right):
		{
			incrementX(speed);
			if (getX() == rightEdge)
			{
				direction = Direction::Left;
			}
			break;
		}
		case(Direction::Left):
		{
			incrementX(-speed);
			if (getX() == leftEdge)
			{
				direction = Direction::Right;
			}
			break;
		}
		default: break;
		}
	}
}

bool BadTurtle::CheckForReceivedDamage()
{
	return false;
}

const CollisionType BadTurtle::getCollisionTypeWith(const Direction& direction, bool onGround)
{
	if (onGround)
	{
		return CollisionType::DealDamage;
	}

	switch (direction)
	{
	case(Direction::Down):
	{
		return CollisionType::ReceiveDamage;
	}
	case(Direction::Right):
	{
		return CollisionType::DealDamage;
	}
	case(Direction::Left):
	{
		return CollisionType::DealDamage;
	}
	default:
		break;
	}

	GameObject::getCollisionTypeWith(direction, onGround);
}