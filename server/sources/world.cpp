#include "../headers/world.h"



World::World()
{

}

World::~World()
{

}

void World::Update(float dt)
{
	for (auto ePlayer : *ePlayers)
	{
		ePlayer->m_SetDt(dt);
	}
	
	//for (auto bullet : *bullets)
	//for (std::vector<std::shared_ptr<Bullet>>::iterator i = bullets->begin(); i != bullets->end();)
	for (size_t i = 0; i < bullets->size(); i++)
	{
		if ((*bullets)[i]->m_Update(dt) == false)
		{
			bullets->erase(bullets->begin() + i);
			break;
		}
	
		//if (bullets->at(i)->m_Update(dt) == true)
		//	i = bullets.erase(i);
		//else
		//	i++
	}

	checkPlayersCollisions();
}

void World::checkPlayersCollisions()
{
	for (auto player : *ePlayers)
	{
		for (auto wall : walls)
		{
			if (wall->m_Overlaps(player))
				player->m_ReactOnCollision();
		}
	}

	for (auto bullet : *bullets)
	{
		for (auto wall : walls)
		{
			bullet->Overlaps(wall);
		}
	
		for (auto player : *ePlayers)
		{
			bullet->Overlaps(player);
		}
	}
}


//private:
//	std::vector<Bullet*> * bullets;
//	std::vector<std::shared_ptr<E_Player>> * ePlayers;
//
//	std::vector<Wall*> walls;
//	std::vector<Floor*> floors;
