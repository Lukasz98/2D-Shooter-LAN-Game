#include "mapObject.h"

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
///std::cout<<"b"<<_path<<"b";
	m_texture.loadFromFile(_path);
	setTexture(&m_texture);
}

