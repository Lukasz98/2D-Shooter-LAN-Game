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
#include "enemy.h"
#include "e_player.h"
#include "body.h"


class World
{
public:
	World();
	~World();

	//void m_Update(Player * _player, std::vector<Bullet*> &_bullets, float _dt);
	void m_Update(Player * _player, float _dt);
	void m_Draw(sf::RenderWindow &_window);

	//void m_ReceivePacket(sf::Packet _packet);

	void m_AddBullet(Bullet * _bullet);

	void m_AddFloor(Floor * _floor);
	void m_AddWall(Wall * _wall);
	void m_AddEnemy(Enemy * _enemy);
	void m_AddEPlayer(E_Player * _ePlayer);

private:
	std::vector<Wall*> m_walls;
	std::vector<Floor*> m_floors;
	std::vector<Enemy*> m_enemies;
	std::vector<E_Player*> m_ePlayers;
	std::vector<Bullet*> m_bullets;

	float m_dt;

	void m_checkBulletsCollision(Body * _playerBody);
	void m_checkBodyCollision(Body * _body);

};


