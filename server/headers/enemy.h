#pragma once
#include <string>
#include "basic_ai.h"

//#include <stdlib.h>
//#include <time.h>



class Enemy : public BasicAI
{
public:
	Enemy(sf::Vector2f _pos);
	~Enemy();


	bool m_Update(float _dt, sf::Vector2f _direction);
	void m_SendPlayerPos(sf::Vector2f _pos);


	void m_SetPosition(sf::Vector2f _pos);
	void m_SetTexture(std::string _texturePath);


private:
	sf::Texture m_texture;
	int m_framesCount;

};

