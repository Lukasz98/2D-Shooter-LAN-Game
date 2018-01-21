#include "../headers/map_object.h"

MapObject::MapObject()
{
}

MapObject::~MapObject()
{
}

void MapObject::SetPosition(sf::Vector2f pos)
{
	this->pos = pos;
	setPosition(pos);
}

void MapObject::SetSize(sf::Vector2f size)
{
	this->size = size;
	setSize(size);
}

void MapObject::SetTexture(std::string path)
{

	texture.loadFromFile(path);
	setTexture(&texture);
}


bool MapObject::Overlaps(const Body * body)
{
	sf::Vector2f bodyPos = body->getPosition();
	sf::Vector2f bodySize = body->getSize();
	bodyPos.x -= bodySize.x /2;
	bodyPos.y -= bodySize.y /2;

	bool collision = true;

	if (bodyPos.x > pos.x + size.x)
		collision = false;
	if (bodyPos.x + bodySize.x < pos.x)
		collision = false;
	if (bodyPos.y > pos.y + size.y)
		collision = false;
	if (bodyPos.y + bodySize.y < pos.y)
		collision = false;

	return collision;
}


