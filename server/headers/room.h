#pragma once
#include <string>
#include <vector>
#include <thread>

#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>

#include "e_player.h"
#include "bullet.h"
#include "load_from_files.h"
#include "log.h"
#include "getch.h"

enum State { RUNNING, STOP, PREPARATION };

class Room
{
public:
	Room();
	~Room();

	void SendData();

	inline State GetState() { return state; }
	std::vector<E_Player*> & GetPlayers() { return ePlayers; }
	std::vector<Bullet*> * GetBullets() { return & bullets; }

private:
	std::vector<E_Player*> ePlayers;
	std::vector<Bullet*> bullets;
	
	std::string ip;
	int joinPort, receivingPort, sendingPort;
	sf::UdpSocket receiveSocket, sendSocket;

	State state = PREPARATION;

	sf::TcpListener tcpListener;

	void loadServerInfo();
	static void waitForPlayers(std::vector<E_Player*> & ePlayers, std::vector<Bullet*> & bullets, const State & state, sf::TcpListener & tcpListener, int receivingPort, int sendingPort); //thread
	static void receiveInput(std::vector<E_Player*> & ePlayers, std::vector<Bullet*> & bullets, const State & state, sf::UdpSocket & socket); //thread
};