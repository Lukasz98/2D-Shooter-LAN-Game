#pragma once
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "world.h"
#include "world_loader.h"

#include "room.h"
#include "e_player.h"
#include "bullet.h"
#include "info.h"
#include "time.h"
#include "kbhit.h"
#include "tile.h"

class Game
{
public:
	Game(Room * room);
	~Game();

private:
	Room * room;
	World * world;
	
	std::vector<std::shared_ptr<Bullet>> * bullets;
	std::vector<std::shared_ptr<E_Player>> * ePlayers;

	Utils::Time time;

	void play();
	void update();
    void updateFlags();
	void collisions();


};
