#pragma once
#include <iostream>
#include "e_player.h"



class Player : public E_Player
{
public:
	Player(int _id, std::string _ip, int _port);
	~Player();



	void m_Update(float _dt, sf::Vector2i _mousePos);



private:


};