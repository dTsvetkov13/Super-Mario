#pragma once

#include "GameObject.h"
#include <string>

class Player : public GameObject
{
private:
	bool isJumping = false;
	bool isFalling = true;
	bool m_onGround = false;
	bool writing = false;
	std::string text = "";
	Direction sideVelocityDirection;
	int jumpLength = 50;
	int targetJump;
	int speed = 5;
	int jumpSpeed = 2;
	int velocityX = 0;
	int startX;
	int startY;
	unsigned int lives = 3;
	std::unique_ptr<DrawingComponent> heart;

	void DrawLives(SDL_Renderer*);
	void ValidatePosition();

	void writingMove(SDL_Event &event);
	void moveEvent(SDL_Event& event);
public:
	Player();
	Player(const tinyxml2::XMLElement*, SDL_Renderer* ren);
	Player(const Player&);
	Player(std::string &path, SDL_Renderer* ren, Cordinates cords, unsigned int heightParts, unsigned int widthParts);
	~Player() override;

	void init(std::string &textureSheet, SDL_Renderer* ren, Cordinates cords, unsigned int heigthPartsCount, unsigned int widthPartsCount);
	void handleEvent(SDL_Event &event);
	void Update() override;
	void Render(SDL_Renderer*) override;
	void Jump();

	void IncreaseLives(int);
	void DecreaseLives(int);
	void GoToStartPos();

	bool onGround();
	inline bool isWriting() { return writing; }

	std::string& getText() { return text; }
};