#include "World.h"
#include "BadTurtle.h"
#include "Camera.h"

#include "../include/SDL2_ttf/include/SDL_ttf.h"

World* World::instance = nullptr;

World::World()
{
}

World::World(World const&)
{

}

World::~World()
{
	delete instance;
}

World* World::Instance()
{
	if (instance == nullptr)
	{
		instance = new World();
	}
	
	return instance;
}

void World::setPlayer(Player const& player)
{
	this->player = std::make_unique<Player>(player);
}

void World::addEnemy(Enemy const& enemy)
{
	std::shared_ptr<UUID> tempId = std::make_unique<UUID>();
	enemies[tempId] = std::make_unique<Enemy>(enemy);
}

void World::setPlayer(std::unique_ptr<Player>& player)
{
	this->player = std::move(player);
	this->player.get()->setId(std::shared_ptr<UUID>());
}

void World::addEnemy(std::unique_ptr<Enemy>& enemy)
{
	std::shared_ptr<UUID> tempId = std::make_unique<UUID>();
	enemies[tempId] = std::move(enemy);
	enemies[tempId].get()->setId(tempId);
}

void World::Update()
{
	player.get()->Update();
	for (auto it = enemies.cbegin(), next_it = it; it != enemies.cend(); it = next_it )
	{
		next_it++;
		
		it->second.get()->InRange(player.get()->getDestRect());
		it->second.get()->Update();
	}
}

void World::Render(SDL_Renderer* ren)
{
	player.get()->Render(ren);
	
	for (auto &it : enemies)
	{
		it.second.get()->Render(ren);
	}

	if(showTextArea)
	{
		drawTextArea(ren);
	}
}

void World::PlayerHandleEvent(SDL_Event & event)
{
	player.get()->handleEvent(event);
}

void World::setPlayerDied(bool b)
{
	playerDied = b;
}

void World::drawTextArea(SDL_Renderer * ren)
{
	SDL_Surface* sur = IMG_Load("../assets/pictures/text-area.png");

	textAreaRect.w = sur->w * 5;
	textAreaRect.h = sur->h * 2;
	textAreaRect.x = player.get()->getDestRect()->x - (textAreaRect.w / 2) + player.get()->getDestRect()->w / 2;
	textAreaRect.y = 20;

	SDL_Texture* text = SDL_CreateTextureFromSurface(ren, sur);

	SDL_RenderCopy(ren, text, NULL, &textAreaRect);

	std::string t = "";

	if (player.get()->getText() != "")
	{
		t = player.get()->getText();
	}
	else
	{
		t = "Please, click here to write text!";
	}

	TTF_Font* Sans = TTF_OpenFont("../assets/ttf/OpenSans-Italic.ttf", 10);

	SDL_Color Black = { 0, 0, 0 };

	sur = TTF_RenderText_Solid(Sans, t.c_str(), Black);

	text = SDL_CreateTextureFromSurface(ren, sur);

	SDL_Rect dest;

	dest.w = sur->w;
	dest.h = sur->h;
	dest.x = textAreaRect.x + 12;
	dest.y = textAreaRect.y + 10;

	SDL_RenderCopy(ren, text, NULL, &dest);

	SDL_FreeSurface(sur);
	SDL_DestroyTexture(text);
}

void World::KillObject(const std::shared_ptr<UUID>& id)
{
	if (player.get()->getId() == id)
	{
		player = nullptr;
	}
	else
	{
		enemies.erase(id);
	}
}

bool World::Collision(const SDL_Rect& dest1, const SDL_Rect& dest2)
{
	if (
		dest1.x + dest1.w >= dest2.x &&
		dest2.x + dest2.w >= dest1.x &&
		dest1.y + dest1.h >= dest2.y &&
		dest2.y + dest2.h >= dest1.y
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool World::InTheTextArea(int x, int y)
{
	SDL_Rect temp;
	temp.x = x - Camera::Instance()->getWindowRect()->x;
	temp.y = y - Camera::Instance()->getWindowRect()->y;
	temp.w = 0;
	temp.h = 0;

	if (Collision(temp, textAreaRect) && showTextArea)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const std::string& World::GetPlayerText()
{
	return player.get()->getText();
}

bool World::PlayerCollision(const SDL_Rect& dest1, const Direction& direction)
{
	for (auto &it : enemies)
	{
		if (Collision(dest1, *it.second.get()->getDestRect()))
		{
			switch (it.second.get()->getCollisionTypeWith(direction, player.get()->onGround()))
			{
			case(CollisionType::DealDamage):
			{
				player.get()->DecreaseLives(1);
				player.get()->GoToStartPos();
				std::cout << "PLAYER KILLED" << std::endl;
				break;
			}
			case(CollisionType::ReceiveDamage):
			{
				enemies.erase(it.first);
				return true;
				break;
			}
			default:
				break;
			}
		}
	}

	return true;
}