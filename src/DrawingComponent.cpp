#include "DrawingComponent.h"
#include <iostream>
#include "Map.h"

DrawingComponent::DrawingComponent()
{
	src.x =	src.y = 0;
	dest.x = dest.y = 0;
	dest.h = dest.w = 64;
}

DrawingComponent::DrawingComponent(std::string path, SDL_Renderer* ren) : DrawingComponent()
{
	texture = getTexture(path, ren);
}

DrawingComponent::~DrawingComponent()
{
	SDL_DestroyTexture(texture);
}

void DrawingComponent::init(std::string path, SDL_Renderer* ren, unsigned int heightParts, unsigned int widthParts)
{
	src.x = 0;
	src.y = 0;
	SDL_Surface* sur = IMG_Load(path.c_str());
	src.h = sur->h;
	src.w = sur->w;
	dest.h = Map::Instance()->getObjectSize() * heightParts;
	dest.w = Map::Instance()->getObjectSize() * widthParts;
	texture = getTexture(path, ren);
}
 
SDL_Texture* DrawingComponent::getTexture(std::string path, SDL_Renderer* ren)
{
	SDL_Surface* sur = IMG_Load(path.c_str());

	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, sur);

	SDL_FreeSurface(sur);
	return tex;
}

SDL_Texture* DrawingComponent::getTexture()
{
	return texture;
}

SDL_Rect* DrawingComponent::getSrcRect()
{
	return &src;
}
SDL_Rect* DrawingComponent::getDestRect()
{
	return &dest;
}

void DrawingComponent::Draw(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren, texture, &src, &dest);
}

void DrawingComponent::Draw(SDL_Renderer* ren, SDL_Rect* dest)
{
	SDL_RenderCopy(ren, texture, &src, dest);
}

void DrawingComponent::Update()
{
	
}