#include "../headers/bullet.h"

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f speedRatio, int ownerId, int bulletId)
{
	position = pos;
	this->ownerId = ownerId;
	this->bulletId = bulletId;
	speed = 1500.0f;
	power = 2.0f;

	this->speedRatio = speedRatio;
	radius = 15.0f;
}

Bullet::~Bullet()
{
//LOG("Bullet::destructor");
}


bool Bullet::Update(float dt)
{
	this->dt = dt;

	position.x += speed * speedRatio.x * dt;
	position.y += speed * speedRatio.y * dt;

	if (power <= 0.0f)
		return false;
	return true;
}

void Bullet::Overlaps(const MapObject * object)
{
	if (isCollision(object->GetPosition(), object->GetSize()))
	{
		CollisionReact(10.0f);
	}
}

void Bullet::Overlaps(std::shared_ptr<E_Player> ePlayer)
{
	if (ePlayer->GetId() == ownerId)
		return;
		
	if (isCollision(ePlayer->GetPosition(), ePlayer->GetSize()))
	{
		CollisionReact(10.0f);
		ePlayer->Damage(51.0f);
	}
}

bool Bullet::isCollision(sf::Vector2f objectPos, sf::Vector2f objectSize)
{
	bool collision = true;
	
	if (position.x > objectPos.x + objectSize.x)
		collision = false;
	if (position.x + radius * 2 < objectPos.x)
		collision = false;
	if (position.y > objectPos.y + objectSize.y)
		collision = false;
	if (position.y +  radius * 2 < objectPos.y)
		collision = false;
	
	return collision;
}



void Bullet::CollisionReact(float power)
{
	this->power -= power;
}
