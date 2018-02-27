#include "../headers/world.h"



World::World()
{

}

World::~World() 
{

}



void World::Draw(sf::RenderWindow & window)
{

//if (ePlayers->size() > 0)   
  //  LOG((*ePlayers)[0]->GetPosition().x << ", " << (*ePlayers)[0]->GetPosition().y);
    
    for (auto tile : tiles)
    {
    //    LOG("tile");
        window.draw(*tile);
    }

    for (auto flag : flags)
        window.draw(*flag);

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


