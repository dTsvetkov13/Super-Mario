#include "Player.h"
#include "Map.h"
#include "World.h"
#include "Game.h"
#include "Camera.h"
#include <iostream>

Player::Player()
{

}

Player::Player(const Player& player)
{
	
}

Player::Player(std::string &path, SDL_Renderer* ren, int startX, unsigned int heightParts, unsigned int widthParts, int startPartsAbove)
	: GameObject(path, ren, startX, heightParts, widthParts, startPartsAbove)
{
	jumpLength = 1.75 * heightParts * Map::Instance()->getObjectSize();
	setTag(GameObjectTag::Player);
	heart = std::make_unique<DrawingComponent>();
	heart->init("../assets/pictures/heart.png", ren, 1, 1);
	this->startX = startX;
	this->startY = startPartsAbove - (Map::Instance()->getObjectSize() * heightParts);;
}

Player::~Player()
{
}

void Player::handleEvent(SDL_Event &event)
{
	if (event.type == SDL_MOUSEMOTION) //&&  event.type == SDL_MOUSEBUTTONDOWN
	{
		checkTheMouseCords(event);
	}
	else if(writing)
	{
		velocityX = 0;
		writingMove(event);
	}
	else
	{
		text = "";
		moveEvent(event);
	}

}

void Player::checkTheMouseCords(SDL_Event & event)
{
	int xMouse, yMouse;
	SDL_GetGlobalMouseState(&xMouse, &yMouse);

	if (event.button.button == SDL_BUTTON_LEFT)
	{
		if (World::Instance()->InTheTextArea(xMouse, yMouse))
		{
			writing = true;
		}
		else
		{
			writing = false;
		}
	}
}

void Player::writingMove(SDL_Event& event)
{
	if (event.type == SDL_TEXTINPUT)
	{
		text += event.text.text;
	}

	if (event.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0 && event.type != SDL_KEYDOWN)
	{
		text = text.substr(0, text.length() - 1);
	}
}

void Player::moveEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYUP:
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
		{
			break;
		}
		case SDLK_d:
		{
			velocityX = 0;
			break;
		}
		case SDLK_a:
		{
			velocityX = 0;
			break;
		}
		case SDLK_RIGHT:
		{
			velocityX = 0;
			break;
		}
		case SDLK_LEFT:
		{
			velocityX = 0;
			break;
		}
		default:
			velocityX = 0;
			break;
		}
		break;
	}
	case SDL_KEYDOWN:
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
		{
			if (!isJumping && m_onGround)
			{
				targetJump = getY() - jumpLength;
				isJumping = true;
				m_onGround = false;
			}
			break;
		}
		case SDLK_w:
		{
			if (!isJumping && m_onGround)
			{
				targetJump = getY() - jumpLength;
				isJumping = true;
				m_onGround = false;
			}
			break;
		}
		case SDLK_d:
		{
			if (isJumping || !m_onGround)
			{
				sideVelocityDirection = Direction::Right;
				velocityX = speed;
			}
			else
			{
				double offset;
				if (Map::Instance()->Collision(this, Direction::Right, speed, offset))
				{
					incrementX(offset);
					break;
				}
				incrementX(speed);
			}
			break;
		}
		case SDLK_a:
		{
			if (isJumping || !m_onGround)
			{
				sideVelocityDirection = Direction::Left;
				velocityX = speed;
			}
			else
			{
				double offset;
				if (Map::Instance()->Collision(this, Direction::Left, speed, offset))
				{
					incrementX(offset);
					break;
				}
				incrementX(-speed);
			}
			break;
		}
		case SDLK_RIGHT:
		{
			if (isJumping || !m_onGround)
			{
				velocityX = speed;
				sideVelocityDirection = Direction::Right;
			}
			else
			{
				double offset;
				if (Map::Instance()->Collision(this, Direction::Right, speed, offset))
				{
					incrementX(offset);
					break;
				}
				incrementX(speed);
			}
			break;
		}
		case SDLK_LEFT:
		{
			if (isJumping || !m_onGround)
			{
				sideVelocityDirection = Direction::Left;
				velocityX = speed;
			}
			else
			{
				double offset;
				if (Map::Instance()->Collision(this, Direction::Left, speed, offset))
				{
					incrementX(offset);
					break;
				}
				incrementX(-speed);
			}
			break;
		}
		default:
			velocityX = 0;
			break;
		}
	}
	default:
		break;
	}
}

void Player::Update()
{
	ValidatePosition();
	GameObject::Update();
	ValidatePosition();
	Camera::Instance()->update(getX(), getWidthPartsCount());
	
	double offset;
	if (!Map::Instance()->Collision(this, sideVelocityDirection, velocityX, offset))
	{
		if (sideVelocityDirection == Direction::Right)
		{
			incrementX(velocityX);
			World::Instance()->PlayerCollision(*getDestRect(), sideVelocityDirection);
		}
		else if(sideVelocityDirection == Direction::Left)
		{
			incrementX(-velocityX);
			World::Instance()->PlayerCollision(*getDestRect(), sideVelocityDirection);
		}
	}
	else
	{
		incrementX(offset);
		World::Instance()->PlayerCollision(*getDestRect(), sideVelocityDirection);
	}
	
	ValidatePosition();
	GameObject::Update();
	ValidatePosition();
	Camera::Instance()->update(getX(), getWidthPartsCount());

	if(isJumping)
	{
		if (getY() == targetJump && !m_onGround)
		{
			isJumping = false;
			double offset;
			if (Map::Instance()->Collision(this, Direction::Down, jumpSpeed, offset))
			{
				incrementY(offset);
				m_onGround = true;
				GameObject::Update();
				World::Instance()->PlayerCollision(*getDestRect(), Direction::Down);
				return;
			}
			incrementY(jumpSpeed);
			GameObject::Update();
			World::Instance()->PlayerCollision(*getDestRect(), Direction::Down);
		}
		else
		{
			double offset;
			if (Map::Instance()->Collision(this, Direction::Up, jumpSpeed, offset))
			{
				incrementY(offset);
				GameObject::Update();
				World::Instance()->PlayerCollision(*getDestRect(), Direction::Up);
				isJumping = false;
				return;
			}
			else
			{
				incrementY(-jumpSpeed);
				GameObject::Update();				
				World::Instance()->PlayerCollision(*getDestRect(), Direction::Up);
			}
		}
	}
	else if (isFalling)
	{
		double offset;
		if (Map::Instance()->Collision(this, Direction::Down, jumpSpeed, offset))
		{
			incrementY(offset);
			m_onGround = true;
			GameObject::Update();
			World::Instance()->PlayerCollision(*getDestRect(), Direction::Down);
			return;
		}
		m_onGround = false;
		incrementY(jumpSpeed);
		GameObject::Update();
		World::Instance()->PlayerCollision(*getDestRect(), Direction::Down);
	}
}

void Player::Render(SDL_Renderer* ren)
{
	GameObject::Render(ren);
	DrawLives(ren);
}

void Player::IncreaseLives(int number)
{
	lives += number;
}

void Player::DecreaseLives(int number)
{
	lives -= number;
}

void Player::GoToStartPos()
{
	incrementX(startX - getX());
	incrementY(startY - getY());
	GameObject::Update();
}

void Player::ValidatePosition()
{
	if (getX() < 0)
	{
		incrementX(-1 * getX());
	}
	else if ((getX() + getWidthPartsCount() * Map::Instance()->getObjectSize()) >= Map::Instance()->getMapWidth())
	{
		incrementX(Map::Instance()->getMapWidth() - (getX() + getWidthPartsCount() * Map::Instance()->getObjectSize()));
	}
}

bool Player::onGround()
{
	return m_onGround;
}

void Player::DrawLives(SDL_Renderer* ren)
{
	SDL_Rect tempDest = *heart->getDestRect();

	if (lives == 0)
	{
		World::Instance()->setPlayerDied(true);
		return;
	}

	for (int i = 0; i < lives; i++)
	{
		tempDest.x = tempDest.w * i;
		heart->Draw(ren, &tempDest);
	}
}