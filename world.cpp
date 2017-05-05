#include "world.h"

World::World()
{
	/*
	sf::Vector2f size = sf::Vector2f(100.0f, 400.0f); 
	sf::Vector2f pos = sf::Vector2f(300.0f, 100.0f);
	sf::RectangleShape rs;
	rs.setSize(size);
	rs.setPosition(pos);
	m_walls.push_back(rs);
	*/
}

World::~World()
{
//std::cout << "\nUSUWANIE MAPY\n";
	for (int i = 0; i < m_floors.size(); i++)
		delete m_floors[i];
	
	for (int i = 0; i < m_walls.size(); i++)
		delete m_walls[i];
}


void World::m_Update(Player * _player, std::vector<Bullet*> &_bullets, float _dt)
{
	m_dt = _dt;
	
	m_checkBodyCollision(_player);	
	m_checkBulletsCollision(_bullets);
	
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_checkBodyCollision(m_enemies[i]);
		m_enemies[i]->m_SendPlayerPos(_player->getPosition());
	}
	
	for (int i = 0; i < m_enemies.size(); i++)        
	{
		if (m_enemies[i]->m_Update(m_dt, _player->getPosition()))
		{
			m_enemies.erase(m_enemies.begin() + i);
			break;
		}
	}
}

void World::m_checkBodyCollision(Body * _body)
{
	sf::Vector2f bodyPos = _body->getPosition();	
	sf::Vector2f bodySize = _body->getSize();
	bodyPos.x -= bodySize.x /2;
	bodyPos.y -= bodySize.y /2;

	for (int i = 0; i < m_walls.size(); i++)
	{
		sf::Vector2f wallPos = m_walls[i]->getPosition();	
		sf::Vector2f wallSize = m_walls[i]->getSize();
		
		bool collision = true;
		if (bodyPos.x > wallPos.x + wallSize.x)
			collision = false;
		if (bodyPos.x + bodySize.x < wallPos.x)
			collision = false;
		if (bodyPos.y > wallPos.y + wallSize.y)
			collision = false;
		if (bodyPos.y + bodySize.y < wallPos.y)
			collision = false;
		
		if (collision == true)
		{
			//std::cout << "kolizja" << playerPos.x << ", " << playerPos.y << std::endl;
			_body->m_ReactOnCollision();
		}
	}
}

void World::m_checkBulletsCollision(std::vector<Bullet*> &_bullets)
{
	for (int s = 0; s < m_walls.size(); s++)
	{
		sf::Vector2f wallPos = m_walls[s]->getPosition();	
		sf::Vector2f wallSize = m_walls[s]->getSize();
		
		for (int b = 0; b < _bullets.size(); b++)
		{
			sf::Vector2f bulletPos = _bullets[b]->getPosition();
			float bulletWidth = _bullets[b]->getRadius() * 2;
			
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
				_bullets[b]->m_CollisionReact(10.0f); // 10 - power
				//std::cout << bulletPos.x << std::endl;
			}
		}
	}
	
	bool alarm = false;
	for (int i = 0; i < _bullets.size(); i++)
	{
		for (int j = 0; j < m_enemies.size(); j++)        
		{
			if (_bullets[i]->m_Overlaps(*m_enemies[j]))
			{
				m_enemies[j]->m_GetDamage(51.0f);
				_bullets.erase(_bullets.begin() + i);
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
