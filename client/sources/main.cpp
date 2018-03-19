#include <iostream>
#include "../headers/connection.h"
#include "../headers/game.h"
#include "../headers/log.h"

int main()
{
    Connection connection;
    
    if (connection.isConnected())
    {
        Game game{ &connection };
        connection.Close();
    }   
}
