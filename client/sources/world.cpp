#include "../headers/world.h"



World::World()
{

}

World::~World() {}



void World::Draw(sf::RenderWindow & window)
{
//	LOG("-");
	for (auto bullet : *bullets)
	{
		//LOG("World:draw x=" << bullet->GetPosition().x);
		window.draw(*bullet);
//	LOG(bullet->GetBulletId());
	}
//	LOG("-");

	for (auto ePlayer : *ePlayers)
		window.draw(*ePlayer);

}

const E_Player * World::GetEPlayer(int id)
{
	for (auto player : *ePlayers)
	{
		if (player->m_GetId() == id)
		{
			return player;
		}
	}
}



