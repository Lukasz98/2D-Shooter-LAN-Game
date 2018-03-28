#include <iostream>
#include "../headers/connection.h"
#include "../headers/game.h"
#include "../headers/log.h"

int main()
{
    bool lanGame = true;
    Connection * connection;

    try
    {
        connection = new Connection(lanGame);
    }
    catch (const char * e)
    {
        LOG(e);
        return 1;
    }
    
    if (connection->isConnected())
    {
        Game game{ connection };
        connection->Close();
    }

    delete connection;
}
