#include "../headers/map_object.h"

MapObject::MapObject()
{
}

MapObject::~MapObject()
{
}

void MapObject::m_SetPosition(sf::Vector2f _pos)
{
	m_pos = _pos;
	setPosition(m_pos);
}

void MapObject::m_SetSize(sf::Vector2f _size)
{
	m_size = _size;
	setSize(m_size);
}

void MapObject::m_SetTexture(std::string _path)
{

	m_texture.loadFromFile(_path);
	setTexture(&m_texture);
}


bool MapObject::m_Overlaps(const Body * _body)
{
	sf::Vector2f bodyPos = _body->getPosition();
	sf::Vector2f bodySize = _body->getSize();
	bodyPos.x -= bodySize.x /2;
	bodyPos.y -= bodySize.y /2;

	bool collision = true;

	if (bodyPos.x > m_pos.x + m_size.x)
		collision = false;
	if (bodyPos.x + bodySize.x < m_pos.x)
		collision = false;
	if (bodyPos.y > m_pos.y + m_size.y)
		collision = false;
	if (bodyPos.y + bodySize.y < m_pos.y)
		collision = false;

	return collision;
}


