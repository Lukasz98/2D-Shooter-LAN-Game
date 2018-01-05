#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

#include "e_player.h"
#include "bullet.h"
#include "log.h"



class World
{
public:
	World();
	~World();

	void Draw(sf::RenderWindow & window);

	void SetPlayers(std::vector<E_Player*> * ePlayers) { this->ePlayers = ePlayers; }
	void SetBullets(std::vector<Bullet*> * bullets) { this->bullets = bullets; }
	void AddBullet(Bullet * bullet) { bullets->push_back(bullet); }

	const E_Player * GetEPlayer(int id);


private:
	std::vector<Bullet*> * bullets;
	std::vector<E_Player*> * ePlayers;

};