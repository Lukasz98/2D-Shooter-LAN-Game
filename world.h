#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "player.h"
#include "bullet.h"


class World
{
public:
	World();
	~World();
	
	void m_Update(Player &_player, std::vector<Bullet*> &_bullets);
	void m_Draw(sf::RenderWindow &_window);
	
private:
	std::vector<sf::RectangleShape> m_shapes;
	
	
	void m_checkBulletsCollision(std::vector<Bullet*> &_bullets);
	void m_checkPlayerCollision(Player &_player);
	
};
