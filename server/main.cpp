#include <iostream>

#include "headers/game.h"
#include "headers/room.h"
#include "headers/log.h"

int main()
{
    std::cout << "Welcome in server" << std::endl;
    
    bool lanGame = true;
    
    Room * room;
    try
    {
        room = new Room(lanGame);
    }
    catch(const char * e)
    {
        LOG(e);
        return 1;
    }

    if (room->GetState() == RUNNING)
    {
        std::cout << "Game is running" << std::endl;
        std::cout << "Press any key to shutdown server" << std::endl;

        Game game(room);
    }
    
    delete room;
    
}
