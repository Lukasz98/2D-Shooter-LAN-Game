#include "../headers/world.h"



World::World()
{

}

World::~World() 
{
	for (auto floor : floors)
		delete floor;

	for (auto wall : walls)
		delete wall;
}



void World::Draw(sf::RenderWindow & window)
{
	for (auto floor : floors)
		window.draw(*floor);

	for (auto wall : walls)
		window.draw(*wall);

	for (auto const ePlayer : (*ePlayers))
		window.draw(*ePlayer);

	for (auto bullet : *bullets)
		window.draw(*bullet);
}

const std::shared_ptr<E_Player> World::GetEPlayer(int id)
{
	for (auto player : *ePlayers)
	{
		if (player->GetId() == id)
		{
			return player;
		}
	}
}



