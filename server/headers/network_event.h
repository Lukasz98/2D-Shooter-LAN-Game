#pragma once
#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>
#include "log.h"

class Event
{
public:
	Event() = delete;
	virtual ~Event() {}
	virtual void PasteData(sf::Packet & packet) = 0;

protected:
	enum EventType { UPDATE = 0, BULLET_DELETE = 1, PLAYER_DELETE = 2 };
	Event(EventType type) : type(type) {}
	EventType type;
};

class BulletDeleteEv : public Event
{
public:
	BulletDeleteEv(int ownerId, int id) 
	: Event(BULLET_DELETE)
	{
		this->ownerId = ownerId;
		this->id = id;
	}
	~BulletDeleteEv() {}

	void PasteData(sf::Packet & packet) override
	{
		packet << type << ownerId << id;
	}

private:
	int ownerId, id;
};

class PlayerDeleteEv : public Event
{
public:
	PlayerDeleteEv(int id) 
	: Event(PLAYER_DELETE)
	{
		this->id = id;
	}
	~PlayerDeleteEv() {}

	void PasteData(sf::Packet & packet) override
	{
		packet << type << id;
	}

private:
	int id;
};