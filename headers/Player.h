#pragma once

#include "GameObject.h"

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
public:
	Player();
	Player(const Player&);
	Player(std::string &path, SDL_Renderer* ren, int startX, unsigned int heightParts, unsigned int widthParts, int startPartsAbove);
	~Player() override;

	void handleEvent(SDL_Event &event);
	void writingMove(SDL_Event &event);
	void checkTheMouseCords(SDL_Event &event);
	void moveEvent(SDL_Event& event);
	void Update() override;
	void Render(SDL_Renderer*) override;

	void IncreaseLives(int);
	void DecreaseLives(int);
	void GoToStartPos();

	bool onGround();
	inline bool isWriting() { return writing; }

	std::string& getText() { return text; }
};