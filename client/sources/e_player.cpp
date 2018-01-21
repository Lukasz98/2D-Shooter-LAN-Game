#include "../headers/e_player.h"

E_Player::E_Player(int id, sf::Vector2f pos, int team)
: Body(sf::Vector2f(pos))
{
	this->id = id;
	this->team = team;

	if (team == 0)
		texture.loadFromFile("img/red_player.png");
	else
		texture.loadFromFile("img/white_player.png");
	size = sf::Vector2f(70.0f, 70.0f);
	setSize(size);
	setOrigin(size.x /2, size.y /2);
	setTexture(&texture);
}

E_Player::~E_Player()
{
//	LOG("EPlayer destructor");
}

void E_Player::Update(sf::Vector2f position, float angle)
{
	SetPosition(position);
	Rotate(angle);
}

