#pragma once

#include "SDL.h"

class Camera
{
private:
	SDL_Rect camera;
	SDL_Rect window;
	static Camera* instance;

	Camera();
	Camera(const Camera&);
public:
	~Camera();

	static Camera* Instance();

	void init(int x, int y, int height, int width);
	void setWindowRect(int x, int y, int height, int width);
	void update(int x, int parts);

	inline SDL_Rect* getCameraRect() { return &camera; }
	inline SDL_Rect* getWindowRect() { return &window; }
};