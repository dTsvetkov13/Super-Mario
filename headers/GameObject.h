#pragma once

#include <string>
#include <map>
#include <memory>
#include <rpc.h>
#include "../include/SDL2/include/SDL.h"
#include "Component.h"
#include "DrawingComponent.h"
#include "../src/Enums.h"

class GameObject
{
public:
	GameObject();
	GameObject(std::string &textureSheet, SDL_Renderer* ren, int startX, unsigned int heigthPartsCount, unsigned int widthPartsCount, double startsAt);
	virtual ~GameObject();

	virtual void Update();
	virtual void Render(SDL_Renderer* ren);
	void incrementX(double x);
	void incrementY(double y);
	inline double getX() { return x; }
	inline double getY() { return y; }
	inline unsigned int getHeigthPartsCount() { return heightPartsCount; }
	inline unsigned int getWidthPartsCount() { return widthPartsCount; }
	
	void setTag(GameObjectTag tag) { this->tag = tag; }
	void setId(std::shared_ptr<UUID>& id) { this->id = id; }

	const SDL_Rect* getDestRect();
	const std::shared_ptr<UUID>& getId() { return id; }
	const GameObjectTag getTag() { return tag; }
	
	virtual const CollisionType getCollisionTypeWith(const Direction&, bool);
private:
	std::shared_ptr<UUID> id;
	SDL_Renderer* ren;
	double x;
	double y;
	unsigned int heightPartsCount = 0;
	unsigned int widthPartsCount = 0;
	std::map<ComponentType, std::unique_ptr<Component>> components;
	std::unique_ptr<DrawingComponent> drawingComponent;
	GameObjectTag tag;
};