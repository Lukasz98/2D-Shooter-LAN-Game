#pragma once
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

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

	void Draw(sf::RenderWindow & window);

	void SetPlayers(std::vector<std::shared_ptr<E_Player>> * ePlayers) { this->ePlayers = ePlayers; }
	void SetBullets(std::vector<Bullet*> * bullets) { this->bullets = bullets; }
	void AddBullet(Bullet * bullet) { bullets->push_back(bullet); }

	void AddWall(Wall * wall) { walls.push_back(wall); }
	void AddFloor(Floor * floor) { floors.push_back(floor); }



	const std::shared_ptr<E_Player> GetEPlayer(int id);


private:
	std::vector<Bullet*> * bullets;
	std::vector<std::shared_ptr<E_Player>> * ePlayers;

	std::vector<Wall*> walls;
	std::vector<Floor*> floors;

};