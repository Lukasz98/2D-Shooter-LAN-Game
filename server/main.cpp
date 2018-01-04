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

	Game::Time time;

	while (!kbhit() || room.GetState() != RUNNING)
	{
//std::vector<E_Player*> ePlayers = room.GetPlayers();

		//if (ePlayers.size() > 0)LOG("X:" << ePlayers.size());
		for (int i = 0; i < ePlayers.size(); i++)
		{
		//LOG("X:" << ePlayers[i]->m_GetPosition().x);
			ePlayers[i]->m_SetDt(time.GetDt());
		}
		

		room.SendData();
		time.Update();
		//LOG("dt="<<time.GetDt());
	}



	//TO DO
	//state = stop
}