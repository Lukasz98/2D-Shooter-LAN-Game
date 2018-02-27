#pragma once
#include <memory>
#include <SFML/System/Vector2.hpp>
#include "math_calc.h"
#include "e_player.h"
#include "map_object.h"
#include "entity.h"
#include "log.h"


class Bullet : public Entity
{
public:
	Bullet(sf::Vector2f pos, sf::Vector2f speedRatio, int ownerId, int bulletId);
	~Bullet();

	bool Update(float dt);
	void CollisionReact(float power);

	void Overlaps(const MapObject * object);
	void Overlaps(std::shared_ptr<E_Player> ePlayer);
	
	//inline const sf::Vector2f & GetPosition() { return position; }
	inline const sf::Vector2f & GetSpeedRatio() { return speedRatio; }
	inline const int & GetOwnerId() { return ownerId; }
	inline const int & GetBulletId() { return bulletId; }
    inline const int & GetRadius() { return size.x; }


private:
	sf::Vector2f speedRatio;
	float dt;
	float speed;
	float power;
	//float radius;
	int ownerId, bulletId;

	void pickDirection();
	void move();
	bool isCollision(sf::Vector2f objectPos, sf::Vector2f objectSize);
};

