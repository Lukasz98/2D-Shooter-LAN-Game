#pragma once
#include <string>
#include <vector>
#include <thread>
#include <memory>

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
	std::vector<std::shared_ptr<E_Player>> * GetPlayers() { return & ePlayers; }
	std::vector<std::shared_ptr<Bullet>> * GetBullets() { return & bullets; }

private:
	std::vector<std::shared_ptr<E_Player>> ePlayers;
	std::vector<std::shared_ptr<Bullet>> bullets;
	
	std::string ip;
	int joinPort, receivingPort, sendingPort;
	sf::UdpSocket receiveSocket, sendSocket;

	State state = PREPARATION;

	sf::TcpListener tcpListener;

int sendingUpdatesCounter = 0;


	void loadServerInfo();
	static void waitForPlayers(std::vector<std::shared_ptr<E_Player>> & ePlayers, const State & state, sf::TcpListener & tcpListener, int receivingPort, int sendingPort); //thread
	static void receiveInput(std::vector<std::shared_ptr<E_Player>> & ePlayers, std::vector<std::shared_ptr<Bullet>> & bullets, const State & state, sf::UdpSocket & socket); //thread
};