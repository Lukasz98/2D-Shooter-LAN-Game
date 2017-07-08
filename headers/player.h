#pragma once
#include <iostream>
#include "e_player.h"



class Player : public E_Player
{
public:
	Player(int _id = 0, std::string _ip = "192.168.1.1", int _port = 54540);
	~Player();

	void m_Move(int _x, int _y);

	void m_Update(float _dt, sf::Vector2i _mousePos);



private:


};
