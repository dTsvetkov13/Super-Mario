#include <iostream>

#include "Camera.h"
#include "Map.h"

Camera* Camera::instance = nullptr;

Camera::Camera()
{
}

Camera::~Camera()
{
	delete instance;
}

Camera * Camera::Instance()
{
	if(instance == nullptr)
	{
		instance = new Camera();
	}

	return instance;
}

void Camera::init(int x, int y, int height, int width)
{
	camera.x = x;
	camera.y = y;
	camera.w = width;
	camera.h = height;
}

void Camera::setWindowRect(int x, int y, int height, int width)
{
	window = { x, y, width, height };
}

void Camera::update(int x, int parts)
{
	double temp = x + parts / 2 * Map::Instance()->getObjectSize();

	if (temp - (camera.w / 2) < 0) camera.x = 0;
	else if (temp + (camera.w / 2) > Map::Instance()->getMapWidth())
	{
		camera.x = Map::Instance()->getMapWidth() - camera.w;
	}
	else
	{
		camera.x = temp - camera.w / 2;
	}
}
