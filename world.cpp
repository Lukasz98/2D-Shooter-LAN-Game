#include "world.h"

World::World()
{
	sf::Vector2f size = sf::Vector2f(100.0f, 400.0f); 
	sf::Vector2f pos = sf::Vector2f(300.0f, 100.0f);
	sf::RectangleShape rs;
	rs.setSize(size);
	rs.setPosition(pos);
	m_shapes.push_back(rs);
}

World::~World()
{
}


void World::m_Update(Player &_player, std::vector<Bullet*> &_bullets)
{
	m_checkPlayerCollision(_player);	
	m_checkBulletsCollision(_bullets);
}

void World::m_checkBulletsCollision(std::vector<Bullet*> &_bullets)
{
	for (int s = 0; s < m_shapes.size(); s++)
	{
		sf::Vector2f shapePos = m_shapes[s].getPosition();	
		sf::Vector2f shapeSize = m_shapes[s].getSize();
		
		for (int b = 0; b < _bullets.size(); b++)
		{
			sf::Vector2f bulletPos = _bullets[b]->getPosition();
			float bulletWidth = _bullets[b]->getRadius() * 2;
			
			bool collision = true;
			if (bulletPos.x > shapePos.x + shapeSize.x)
				collision = false;
			if (bulletPos.x + bulletWidth < shapePos.x)
				collision = false;
			if (bulletPos.y > shapePos.y + shapeSize.y)
				collision = false;
			if (bulletPos.y + bulletWidth < shapePos.y)
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

	for (int i = 0; i < m_shapes.size(); i++)
	{
		sf::Vector2f shapePos = m_shapes[i].getPosition();	
		sf::Vector2f shapeSize = m_shapes[i].getSize();
		
		bool collision = true;
		if (playerPos.x > shapePos.x + shapeSize.x)
			collision = false;
		if (playerPos.x + playerSize.x < shapePos.x)
			collision = false;
		if (playerPos.y > shapePos.y + shapeSize.y)
			collision = false;
		if (playerPos.y + playerSize.y < shapePos.y)
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
	for (int i = 0; i < m_shapes.size(); i++)
		_window.draw(m_shapes[i]);
}
