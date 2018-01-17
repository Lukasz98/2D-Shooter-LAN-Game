#include <iostream>
#include <vector>

#include <SFML/System/Clock.hpp>

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
	std::cout << "Pressing any key to shutdown server" << std::endl;

	std::vector<E_Player*> & ePlayers = room.GetPlayers();
	std::vector<Bullet*> * bullets = room.GetBullets();

	Game::Time time;

	while (!kbhit() || room.GetState() != RUNNING)
	{
		for (int i = 0; i < ePlayers.size(); i++)
		{
			ePlayers[i]->m_SetDt(time.GetDt());
		}

		for (auto bullet : *bullets)
		{
			bullet->m_Update(time.GetDt());
		}
		

		room.SendData();
		time.Update();

	}


	//TO DO
	//state = stop
}