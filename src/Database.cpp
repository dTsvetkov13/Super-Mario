#include "Database.h"
#include "World.h"
#include "Map.h"
#include "BadTurtle.h"
#include "Enemy.h"

#include <iostream>


Database::Database()
{
	tinyxml2::XMLError eResult = m_doc.LoadFile("../Database/db.xml");
	if (eResult != tinyxml2::XML_SUCCESS) std::cout << "EXCEPTION";
}


Database::~Database()
{
}

Database* Database::instance = nullptr;

Database* Database::Instance()
{
	if (instance == nullptr)
	{
		instance = new Database();
	}

	return instance;
}

void Database::LoadGame(SDL_Renderer* ren)
{
	LoadCamera(ren);
	LoadMap(ren);
	LoadGameObjects(ren);
}

void Database::LoadMap(SDL_Renderer* ren)
{

}

void Database::LoadGameObjects(SDL_Renderer* ren)
{
	tinyxml2::XMLElement* root = m_doc.RootElement();
	tinyxml2::XMLElement* objects = root->FirstChildElement("GameObjects");

	if (root->FirstChildElement("Map"))
	{
		Map::Instance()->init(root->FirstChildElement("Map"));
	}

	if (root->FirstChildElement("Player"))
	{
		World::Instance()->setPlayer(std::make_unique<Player>(root->FirstChildElement("Player"), ren));
	}

	tinyxml2::XMLElement* temp = objects->FirstChildElement("BadTurtles")->FirstChildElement("BadTurtle");

	if (temp)
	{
		std::cout << "BAD TURTLE 1" << std::endl;
		std::unique_ptr<Enemy> d = std::make_unique<BadTurtle>(temp, ren);
		World::Instance()->addEnemy(d);
		
		while (true)
		{
			temp = temp->NextSiblingElement();
			if (!temp) break;
			else
			{
				std::cout << "BAD TURTLE 2" << std::endl;
				
				d = std::make_unique<BadTurtle>(temp, ren);
				World::Instance()->addEnemy(d);
			}
		}
	}
	
	temp = objects->FirstChildElement("SeverusSnape");
	
	if (temp)
	{
		std::cout << "SEVERUS SNAPE" << std::endl;
	}

}

void Database::LoadCamera(SDL_Renderer* ren)
{

}