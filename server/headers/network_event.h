#pragma once
#include <vector>
#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>
#include "log.h"

class Event
{
public:
	Event() = delete;
	virtual ~Event() {}
	virtual void PasteData(sf::Packet & packet) = 0;
    
   // virtual void AddData(int,int,int,float,float) = 0; // only for flagsUpdateEvent

protected:
	enum EventType { UPDATE = 0, BULLET_DELETE = 1, PLAYER_DELETE = 2, FLAGS_UPDATE = 3 };
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
    virtual ~BulletDeleteEv() {}

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
	virtual ~PlayerDeleteEv() {}

	void PasteData(sf::Packet & packet) override
	{
		packet << type << id;
	}

private:
	int id;
};

class FlagsUpdateEv : public Event
{
public:
    FlagsUpdateEv()
    : Event(FLAGS_UPDATE)
    {}
    virtual ~FlagsUpdateEv() {}
    
    void AddData(int id, int owner, int isTaking, float neutral, float last)
    {
        //data.push_back(Data(id, owner, isTaking, neutral, last));
        data.push_back(Data{id, owner, isTaking, neutral, last});
    }

    void PasteData(sf::Packet & packet) override
    {
      //LOG("PasteData size="<<data.size());
        packet << type;
        packet << (int)data.size(); //size is always small
        for (auto & d : data)
            packet << d.id << d.owner << d.isTaking << d.neutral << d.last;
    }

private:
    struct Data
    {/*
        Data(int i, int o , int is, float n, float l)
        {
            id = i;
            owner = o;
            isTaking = is;
            neutral = n;
            last = l;
        }*/
        int id;
        int owner, isTaking;
        float neutral, last;
    };
    std::vector<Data> data;
};
