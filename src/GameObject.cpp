#include <iostream>

#include "GameObject.h"
#include "Map.h"
#include "Camera.h"

GameObject::GameObject()
{

}

GameObject::GameObject(std::string &textureSheet, SDL_Renderer* ren, int startX, unsigned int heightPartsCount, unsigned int widthPartsCount, double startsAt)
{
	this->x = startX;
	this->y = startsAt - (Map::Instance()->getObjectSize() * heightPartsCount);
	this->ren = ren;
	this->heightPartsCount = heightPartsCount;
	this->widthPartsCount = widthPartsCount;
	drawingComponent = std::make_unique<DrawingComponent>();
	drawingComponent->init(textureSheet, ren, heightPartsCount, widthPartsCount);
}


GameObject::~GameObject()
{
	ren = nullptr;
}

void GameObject::Update()
{
	SDL_Rect* temp = drawingComponent->getDestRect();
	temp->x = (int)x - Camera::Instance()->getCameraRect()->x;
	temp->y = (int)y;
}

void GameObject::Render(SDL_Renderer* ren)
{
	drawingComponent->Draw(ren);
}

void GameObject::incrementX(double x)
{
	this->x += x;
}

void GameObject::incrementY(double y)
{
	this->y += y;
}

const SDL_Rect* GameObject::getDestRect()
{
	return drawingComponent.get()->getDestRect();
}

const CollisionType GameObject::getCollisionTypeWith(const Direction&, bool)
{
	return CollisionType::DealDamage;
}