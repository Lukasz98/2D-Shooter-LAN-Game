#pragma once
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>


#include "body.h"

#include "e_player.h"
#include "bullet.h"
#include "wall.h"
#include "floor.h"
#include "log.h"



class World
{
public:
	World();
	~World();

	void Update(float dt);

//	void SetPlayers(std::vector<std::shared_ptr<E_Player>> * ePlayers) { this->ePlayers = ePlayers; }
//	void SetBullets(std::vector<std::shared_ptr<Bullet>> * bullets) { this->bullets = bullets; }

	void AddWall(Wall * wall) { walls.push_back(wall); }
	void AddFloor(Floor * floor) { floors.push_back(floor); }
	void SetRedResp(sf::Vector2f pos) { redResp = pos; Body::RED_RESP = redResp; }
	void SetWhiteResp(sf::Vector2f pos) { whiteResp = pos; Body::WHITE_RESP = whiteResp; }

	std::vector<Wall*> & GetWalls() { return walls; }

private:
//	std::vector<std::shared_ptr<Bullet>> * bullets;
//	std::vector<std::shared_ptr<E_Player>> * ePlayers;

	std::vector<Wall*> walls;
	std::vector<Floor*> floors;

	sf::Vector2f redResp, whiteResp;

	void checkPlayersCollisions();


};