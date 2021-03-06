#pragma once
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "connection.h"
#include "world.h"
#include "world_loader.h"
#include "e_player.h"
#include "bullet.h"
#include "info.h"
#include "time.h"
#include "input_data.h"
#include "bottom_bar.h"


class Game
{
public:
    Game(Connection * connection);
    ~Game();

private:
    Connection * connection;
    World * world;
    
    sf::RenderWindow window;
    sf::View view;

    std::vector<E_Player*> * ePlayers;
    std::vector<Bullet*> * bullets;

    E_Player * myPlayer;
    int myId, bulletIds = 0;

    Utils::Time time;
    Utils::InputData inputData;

    int won = 0;

    void play();
    void playerInput();

    //    enum class TEAM { NAZI = 1, POL = 2 };

};
