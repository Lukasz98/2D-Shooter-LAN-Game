#pragma once
#include <string>
#include "basicAI.h"

//#include <stdlib.h>
//#include <time.h>



class Enemy : public BasicAI
{
public:
    Enemy();
    ~Enemy();


    bool m_Update(float _dt, sf::Vector2f _direction);
    void m_SendPlayerPos(sf::Vector2f _pos);

    
    void m_SetPosition(sf::Vector2f _pos);
	void m_SetTexture(std::string _texturePath);


private:
	sf::Texture m_texture;
	//sf::Vector2f m_position;
	//sf::Vector2f m_speedRatio;

	//float m_speed;
	//float m_dt;
	int m_framesCount;

};
