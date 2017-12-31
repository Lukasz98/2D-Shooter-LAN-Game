#include "../headers/world.h"

World::World()
{

}

World::~World()
{
//std::cout << "\nUSUWANIE MAPY\n";
	for (int i = 0; i < m_floors.size(); i++)
		delete m_floors[i];

	for (int i = 0; i < m_walls.size(); i++)
		delete m_walls[i];
}


void World::m_Update(Player * _player, float _dt)
{
	m_dt = _dt;

	for (int i = 0; i < m_ePlayers.size(); i++)
		m_ePlayers[i]->m_SetDt(m_dt);

	m_checkBodyCollision(_player);
	m_checkBulletsCollision(_player);

	for (int i = 0; i < m_ePlayers.size(); i++)
	{
		m_checkBodyCollision(m_ePlayers[i]);
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_checkBodyCollision(m_enemies[i]);
		if (m_enemies[i]->m_IsInViewArea(_player))
		{
			Bullet * b = m_enemies[i]->m_MakeShot(_player->getPosition());
			if (b != NULL)
				m_bullets.push_back(b);
		}
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		if (m_enemies[i]->m_Update(m_dt, _player->getPosition()))
		{
			m_enemies.erase(m_enemies.begin() + i);
			break;
		}
	}

	for (int i = 0; i < m_bullets.size(); i++)
	{
		bool alarm = false;
		bool bulletAlive = m_bullets[i]->m_Update(m_dt);
		if (!bulletAlive)
		{
			m_bullets.erase(m_bullets.begin() + i);
			break;
		}
	}
}

void World::m_checkBodyCollision(Body * _body)
{
	for (int i = 0; i < m_walls.size(); i++)
	{
		if (m_walls[i]->m_Overlaps(_body))
			_body->m_ReactOnCollision();
	}
}

void World::m_checkBulletsCollision(Body * _playerBody )
{
	for (int s = 0; s < m_walls.size(); s++)
	{
		sf::Vector2f wallPos = m_walls[s]->getPosition();
		sf::Vector2f wallSize = m_walls[s]->getSize();

		for (int b = 0; b < m_bullets.size(); b++)
		{
			sf::Vector2f bulletPos = m_bullets[b]->getPosition();
			float bulletWidth = m_bullets[b]->getRadius() * 2;

			bool collision = true;
			if (bulletPos.x > wallPos.x + wallSize.x)
				collision = false;
			if (bulletPos.x + bulletWidth < wallPos.x)
				collision = false;
			if (bulletPos.y > wallPos.y + wallSize.y)
				collision = false;
			if (bulletPos.y + bulletWidth < wallPos.y)
				collision = false;

			if (collision == true)
			{
				m_bullets[b]->m_CollisionReact(10.0f);
			}
		}
	}

	bool alarm = false;
	for (int i = 0; i < m_bullets.size(); i++)
	{
		for (int j = 0; j < m_enemies.size(); j++)
		{
			if (m_bullets[i]->m_Overlaps(m_enemies[j]))
			{
				m_enemies[j]->m_Damage(51.0f);
				m_bullets.erase(m_bullets.begin() + i);
				alarm = true;
				break;
			}
		}

		if (alarm)
			break;

		if (m_bullets[i]->m_Overlaps(_playerBody))
		{
			_playerBody->m_Damage(20.0f);
			m_bullets.erase(m_bullets.begin() + i);
			alarm = true;
			break;
		}

		if (alarm)
			break;

		for (int j = 0; j < m_ePlayers.size(); j++)
		{
			if (m_bullets[i]->m_Overlaps(m_ePlayers[j]))
			{
				m_ePlayers[j]->m_Damage(20.0f);
				m_bullets.erase(m_bullets.begin() + i);
				alarm = true;
				break;
			}
		}

		if (alarm)
			break;
	}
}




void World::m_Draw(sf::RenderWindow &_window)
{
	for (int i = 0; i < m_floors.size(); i++)
		_window.draw(*m_floors[i]);

	for (int i = 0; i < m_walls.size(); i++)
		_window.draw(*m_walls[i]);

	for (int i = 0; i < m_enemies.size(); i++)
		_window.draw(*m_enemies[i]);

	for (int i = 0; i < m_bullets.size(); i++)
		_window.draw(*m_bullets[i]);

	for (int i = 0; i < m_ePlayers.size(); i++)
		_window.draw(*m_ePlayers[i]);
}

void World::m_AddBullet(Bullet * _bullet)
{
	m_bullets.push_back(_bullet);
}

void World::m_AddFloor(Floor * _floor)
{
	m_floors.push_back(_floor);
}

void World::m_AddWall(Wall * _wall)
{
	m_walls.push_back(_wall);
}

void World::m_AddEnemy(Enemy * _enemy)
{
	m_enemies.push_back(_enemy);
}

void World::m_AddEPlayer(E_Player * _ePlayer)
{
	m_ePlayers.push_back(_ePlayer);
}
