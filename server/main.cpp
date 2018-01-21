#include <iostream>

#include "headers/game.h"
#include "headers/room.h"
#include "headers/log.h"

int main()
{
	std::cout << "Welcome in server" << std::endl;
	std::cout << "Pressing any key stops server" << std::endl;

	Room room;

	if (room.GetState() == RUNNING)
	{
		std::cout << "Game is running" << std::endl;
		std::cout << "Press any key to shutdown server" << std::endl;

		Game game(&room);
	}

	return 0;
}
