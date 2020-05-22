#include "..\headers\SeverusSnape.h"	
#include "Camera.h"
#include "World.h"

#include "../include/SDL2_ttf/include/SDL_ttf.h"

SeverusSnape::SeverusSnape()
{

}

SeverusSnape::SeverusSnape(std::string & textureSheet, SDL_Renderer * ren, int startX, unsigned int heigthPartsCount, unsigned int widthPartsCount, double startsAt) :
	Enemy(textureSheet, ren, startX, heigthPartsCount, widthPartsCount, startsAt)
{
}

SeverusSnape::~SeverusSnape()
{
}

bool SeverusSnape::InRange(const SDL_Rect * dest)
{
	if ((dest->x + dest->w + Camera::Instance()->getCameraRect()->x) >= (getX() - rangeInPixels))
	{
		inRange = true;
		World::Instance()->setShowTextArea(true);
		return true;
	}
	else
	{
		World::Instance()->setShowTextArea(false);
		inRange = false;
	}
	return false;
}

void SeverusSnape::Update()
{
	GameObject::Update();

	if (World::Instance()->GetPlayerText() == "")
	{
		return;
	}

	bool matched = false;
	int index = 0;
	std::string temp = "always";

	for (auto &it : World::Instance()->GetPlayerText())
	{
		if (tolower(it) == temp[index])
		{
			if (matched == true || index == 0) index++;

			matched = true;
		}
		else
		{
			matched = false;
			return;
		}
	}

	if (matched && index == temp.length())
	{
		World::Instance()->KillObject(getId());
		World::Instance()->setShowTextArea(false);
	}
}

void SeverusSnape::Render(SDL_Renderer* ren)
{
	if (inRange)
	{
		std::string phrase = "After all this time?";
		SayAPhrase(phrase, ren);
	}

	GameObject::Render(ren);
}

void SeverusSnape::SayAPhrase(std::string&, SDL_Renderer* renderer)
{
	TTF_Font* Sans = TTF_OpenFont("../assets/ttf/OpenSans-Italic.ttf", 24);

	SDL_Color White = { 255, 255, 255 };

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "After all this time?", White);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect dest;
	
	dest.w = surfaceMessage->w;
	dest.h = surfaceMessage->h;
	dest.x = getX() - (Camera::Instance()->getCameraRect()->x + ((dest.w - getDestRect()->w) / 2));
	dest.y = getY() - (dest.h + 20);

	SDL_RenderCopy(renderer, Message, NULL, &dest);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}