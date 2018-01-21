#include "../headers/game.h"

Game::Game(Room * room)
{
	this->room = room;
	world = WorldLoader::LoadMap("../worlds/" + room->GetMapName());

	ePlayers = room->GetPlayers();
	bullets = room->GetBullets();

	play();
}

Game::~Game()
{
	delete world;
}


void Game::play()
{
	while (!kbhit() || room->GetState() != RUNNING)
	{
		update();

		room->SendData();
		time.Update();
	}
}

void Game::update()
{
	for (auto ePlayer : *ePlayers)
	{
		ePlayer->SetDt(time.GetDt());
	}

	for (size_t i = 0; i < ePlayers->size(); i++)
	{
		if ((*ePlayers)[i]->IsOnline() == false)
		{
			PlayerDeleteEv * event = new PlayerDeleteEv((*ePlayers)[i]->GetId());
			room->AddEvent(event);
			room->DeletePlayer(i);
			break;
		}
	}


	for (size_t i = 0; i < bullets->size(); i++)
	{
		if ((*bullets)[i]->Update(time.GetDt()) == false)
		{
			BulletDeleteEv * event = new BulletDeleteEv((*bullets)[i]->GetOwnerId(), (*bullets)[i]->GetBulletId());
			room->AddEvent(event);
			bullets->erase(bullets->begin() + i);
			break;
		}
	}

	collisions();
}


void Game::collisions()
{
	std::vector<Wall*> & walls = world->GetWalls();

	for (auto player : *ePlayers)
	{
		for (auto wall : walls)
			if (wall->Overlaps(player))
				player->ReactOnCollision();
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
