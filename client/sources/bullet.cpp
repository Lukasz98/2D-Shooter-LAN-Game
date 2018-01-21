#include "../headers/bullet.h"

Bullet::Bullet(sf::Vector2f pos, sf::Vector2i mousePos, int ownerId, int bulletId)
{
	texture.loadFromFile("img/texture.png");
	position = pos;
	speed = 1000.0f;
	this->ownerId = ownerId;
	this->bulletId = bulletId;

	mousePos.x += pos.x - SCREEN_WIDTH / 2.0;
	mousePos.y += pos.y - SCREEN_HEIGHT / 2.0;
	sf::Vector2f direction = sf::Vector2f(mousePos.x, mousePos.y);
	speedRatio = Math_calc::Get_xy_SpeedRatio(position, direction);
	
	setRadius(15.0f);
	setPosition(position);
	setTexture(&texture);
}

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f speedRatio, int ownerId, int bulletId)
{
	texture.loadFromFile("img/texture.png");
	position = pos;
	speedRatio = speedRatio;
	speed = 1000.0f;
	this->ownerId = ownerId;
	this->bulletId = bulletId;
	
	setRadius(15.0f);
	setPosition(position);
	setTexture(&texture);
}

Bullet::~Bullet()
{
//LOG("Bullet::destructor");
}


void Bullet::Update(float dt)
{
	this->dt = dt;

	position.x += speed * speedRatio.x * dt;
	position.y += speed * speedRatio.y * dt;

	setPosition(position);
}
