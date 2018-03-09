#include "../headers/e_player.h"

E_Player::E_Player(int id, sf::Vector2f pos, int team)
: Body(sf::Vector2f(pos))
{
	this->id = id;
	this->team = team;

	if (team == 1)
		texture.loadFromFile("img/nazi_player.png");
	else
		texture.loadFromFile("img/pol_player.png");
	size = sf::Vector2f(70.0f, 70.0f);
	setSize(size);
	setOrigin(size.x /2, size.y /2);
	setTexture(&texture);


	
  if (!font.loadFromFile("img/arial.ttf"))
  {
	LOG("World:: font load failed!");
  }

  name = "Lukasz";
  text.setFont(font);
  text.setCharacterSize(25);
  text.setString(name);
  text.setColor(sf::Color::Red);
 
}

E_Player::~E_Player()
{
//	LOG("EPlayer destructor");
}

void E_Player::Update(sf::Vector2f position, float angle)
{
	SetPosition(position);
	text.setPosition(position.x - text.getCharacterSize() * (name.size()/4.0f), position.y + size.y / 2.0f);
	Rotate(angle);
}

