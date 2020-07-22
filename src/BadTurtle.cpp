#include "../headers/BadTurtle.h"
#include "../headers/World.h"
#include <string>
#include "Map.h"

BadTurtle::BadTurtle() : Enemy()
{
}

BadTurtle::BadTurtle(const BadTurtle&)
{

}

BadTurtle::BadTurtle(const tinyxml2::XMLElement *xmlElement, SDL_Renderer *ren)
{
	double x = std::stod(xmlElement->FirstChildElement("x")->GetText());
	double y = std::stod(xmlElement->FirstChildElement("y")->GetText());

	this->speed = std::stod(xmlElement->FirstChildElement("speed")->GetText());

	unsigned int heigthPartsCount = std::stoi(xmlElement->FirstChildElement("heightPartsCount")->GetText());
	unsigned int widthPartsCount = std::stoi(xmlElement->FirstChildElement("widthPartsCount")->GetText());

	double leftEdge = std::stod(xmlElement->FirstChildElement("leftEdge")->GetText());

	std::string temp = "../assets/pictures/bad-turtle.jpg";

	this->init(temp, ren, Cordinates(x, y), heigthPartsCount, widthPartsCount, leftEdge);
	GameObject::init(temp, ren, Cordinates(x, y), heigthPartsCount, widthPartsCount);
}

BadTurtle::BadTurtle(std::string &textureSheet, SDL_Renderer* ren, Cordinates cords, unsigned int heigthPartsCount, unsigned int widthPartsCount, double leftEdge)
	: Enemy(textureSheet, ren, cords, heigthPartsCount, widthPartsCount)
{
	init(textureSheet, ren, cords, heigthPartsCount, widthPartsCount, leftEdge);
}

BadTurtle::~BadTurtle()
{

}

void BadTurtle::init(std::string & textureSheet, SDL_Renderer * ren, Cordinates cords, unsigned int heigthPartsCount, unsigned int widthPartsCount, double leftEdge)
{
	this->leftEdge = leftEdge;
	direction = Direction::Right;
	this->rightEdge = leftEdge + Map::Instance()->getObjectSize() * 2;
}

void BadTurtle::Update()
{
	Move();
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
		World::Instance()->PlayerJump();
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