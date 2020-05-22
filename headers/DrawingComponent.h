#pragma once

#include "Component.h"
#include "../include/SDL2/include/SDL.h"
#include "../include/SDL2_image/include/SDL_image.h"
#include <string>

class DrawingComponent :
	public Component
{
private:
	SDL_Texture* texture;
	SDL_Rect src, dest;
public:
	DrawingComponent();
	DrawingComponent(std::string path, SDL_Renderer* ren);
	~DrawingComponent() override;

	void init(std::string path, SDL_Renderer* ren, unsigned int heightParts, unsigned int widthParts);
	static SDL_Texture* getTexture(std::string path, SDL_Renderer* ren);
	SDL_Texture* getTexture();
	SDL_Rect* getSrcRect();
	SDL_Rect* getDestRect();

	void Draw(SDL_Renderer* ren) override;
	void Draw(SDL_Renderer* ren, SDL_Rect* dest);
	void Update() override;
};