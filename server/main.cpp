#include <iostream>
#include <vector>

#include <SFML/System/Clock.hpp>

#include "headers/world.h"
#include "headers/world_loader.h"
#include "headers/e_player.h"
#include "headers/room.h"
#include "headers/kbhit.h"
#include "headers/log.h"
#include "headers/time.h"


void game(Room & room);

int main()
{
	std::cout << "Welcome in server" << std::endl;
	std::cout << "Pressing any key stops server" << std::endl;


	Room room;

	if (room.GetState() == RUNNING)
	{
		game(room);
	}

	return 0;
}

void game(Room & room)
{
	std::cout << "Game is running" << std::endl;
	std::cout << "Press any key to shutdown server" << std::endl;

//	std::vector<E_Player*> & ePlayers = room.GetPlayers();
//	std::vector<Bullet*> * bullets = room.GetBullets();

	Game::Time time;
World * world = WorldLoader::LoadMap("../worlds/testWorld");
world->SetPlayers(room.GetPlayers());
world->SetBullets(room.GetBullets());

	while (!kbhit() || room.GetState() != RUNNING)
	{

		world->Update(time.GetDt());
	//return;
		

		room.SendData();
		time.Update();

	}
delete world;

	//TO DO
	//state = stop
}