#pragma once

#include <vector>
#include <map>
#include <rpc.h>
#include "Player.h"
#include "Enemy.h"

class World
{
private:
	static World* instance;

	std::unique_ptr<Player> player;
	std::map<std::shared_ptr<UUID>, std::unique_ptr<Enemy>> enemies;
	bool playerDied = false;
	bool showTextArea = true;
	SDL_Rect textAreaRect;

	World();
	World(World const&);
public:
	~World();
	static World* Instance();

	void setPlayer(Player const&);
	void addEnemy(Enemy const&);

	void setPlayer(std::unique_ptr<Player>&);
	void addEnemy(std::unique_ptr<Enemy>&);

	void Update();
	void Render(SDL_Renderer*);
	void PlayerHandleEvent(SDL_Event &event);
	void setPlayerDied(bool);
	void setShowTextArea(bool b) { showTextArea = b; }
	void drawTextArea(SDL_Renderer*);
	void KillObject(const std::shared_ptr<UUID>&);

	bool PlayerCollision(const SDL_Rect&, const Direction&);
	bool Collision(const SDL_Rect&, const SDL_Rect&);
	bool GetPlayerDied();
	bool InTheTextArea(int x, int y);

	const std::string& GetPlayerText();
};