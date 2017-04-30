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
std::cout << "\nUSUWANIE MAPY\n";
	for (int i = 0; i < m_floors.size(); i++)
		delete m_floors[i];
	
	for (int i = 0; i < m_walls.size(); i++)
		delete m_walls[i];
}


void World::m_Update(Player &_player, std::vector<Bullet*> &_bullets)
{
	m_checkPlayerCollision(_player);	
	m_checkBulletsCollision(_bullets);
}

void World::m_AddFloor(Floor * _floor)
{
	m_floors.push_back(_floor);
}

void World::m_AddWall(Wall * _wall)
{
	m_walls.push_back(_wall);
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
}


void World::m_checkPlayerCollision(Player &_player)
{
	sf::Vector2f playerPos = _player.getPosition();	
	sf::Vector2f playerSize = _player.getSize();
	playerPos.x -= playerSize.x /2;
	playerPos.y -= playerSize.y /2;

	for (int i = 0; i < m_walls.size(); i++)
	{
		sf::Vector2f wallPos = m_walls[i]->getPosition();	
		sf::Vector2f wallSize = m_walls[i]->getSize();
		
		bool collision = true;
		if (playerPos.x > wallPos.x + wallSize.x)
			collision = false;
		if (playerPos.x + playerSize.x < wallPos.x)
			collision = false;
		if (playerPos.y > wallPos.y + wallSize.y)
			collision = false;
		if (playerPos.y + playerSize.y < wallPos.y)
			collision = false;
		
		if (collision == true)
		{
			//std::cout << "kolizja" << playerPos.x << ", " << playerPos.y << std::endl;
			_player.m_ReactOnCollision();
		}
	}
}

	
void World::m_Draw(sf::RenderWindow &_window)
{	
	//sf::Texture t;
	//t.loadFromFile("grass.png");
	//m_floors[0]->setTexture(&t);
	for (int i = 0; i < m_floors.size(); i++)
	{
	//std::cout << m_floors[i]->m_pos.x << std::endl;
		_window.draw(*m_floors[i]);
	}		

	for (int i = 0; i < m_walls.size(); i++)
		_window.draw(*m_walls[i]);		
}


