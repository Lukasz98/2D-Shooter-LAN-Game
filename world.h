#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "player.h"
#include "bullet.h"
#include "floor.h"
#include "wall.h"


class World
{
public:
	World();
	~World();
	
	void m_Update(Player &_player, std::vector<Bullet*> &_bullets);
	void m_Draw(sf::RenderWindow &_window);
	
	void m_AddFloor(Floor * _floor);
	void m_AddWall(Wall * _wall);
		
public:
	std::vector<Wall*> m_walls;
	std::vector<Floor*> m_floors;
	
	void m_checkBulletsCollision(std::vector<Bullet*> &_bullets);
	void m_checkPlayerCollision(Player &_player);
	
};



	
