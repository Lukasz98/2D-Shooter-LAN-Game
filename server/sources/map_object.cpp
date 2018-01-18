#include "../headers/map_object.h"

MapObject::MapObject()
{
}

MapObject::~MapObject()
{
}

bool MapObject::m_Overlaps(const std::shared_ptr<Body> _body)
{
	sf::Vector2f bodyPos = _body->m_GetPosition();
	sf::Vector2f bodySize = _body->m_GetSize();
	bodyPos.x -= bodySize.x /2;
	bodyPos.y -= bodySize.y /2;
	
//	LOG("MAPOBJECT:OVERLAPS");

	bool collision = true;

	if (bodyPos.x > m_pos.x + m_size.x)
		collision = false;
	if (bodyPos.x + bodySize.x < m_pos.x)
		collision = false;
	if (bodyPos.y > m_pos.y + m_size.y)
		collision = false;
	if (bodyPos.y + bodySize.y < m_pos.y)
		collision = false;

//	LOG("MAPOBJECT:OVERLAPS " << collision);


	return collision;
}


