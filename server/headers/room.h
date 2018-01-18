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

struct WaitForPlayersData
{
	WaitForPlayersData() {}
	~WaitForPlayersData() {}
	int receivingPort;
	int * redTeam, * whiteTeam;
	std::string mapName;
};

class Room
{
public:
	Room();
	~Room();

	void SendData();
	void SendEvent() {}

	inline State GetState() { return state; }
	std::vector<std::shared_ptr<E_Player>> * GetPlayers() { return & ePlayers; }
	std::vector<std::shared_ptr<Bullet>> * GetBullets() { return & bullets; }

	inline const std::string & GetMapName() { return mapName; }

private:
	std::string mapName = "testWorld";

	int redTeam = 0, whiteTeam = 0; // counting players in teams
	std::vector<std::shared_ptr<E_Player>> ePlayers;
	std::vector<std::shared_ptr<Bullet>> bullets;
	
	std::string ip;
	int joinPort, receivingPort, sendingPort;
	sf::UdpSocket receiveSocket, sendSocket;

	State state = PREPARATION;

	sf::TcpListener tcpListener;

int sendingUpdatesCounter = 0;

WaitForPlayersData waitForPlayersData;

	void loadServerInfo();

	static void waitForPlayers(std::vector<std::shared_ptr<E_Player>> & ePlayers, const State & state, sf::TcpListener & tcpListener, WaitForPlayersData & waitForPlayersData); //thread
//	static void waitForPlayers(std::vector<std::shared_ptr<E_Player>> & ePlayers, const State & state, sf::TcpListener & tcpListener, int receivingPort, std::string mapName); //thread
	static void receiveInput(std::vector<std::shared_ptr<E_Player>> & ePlayers, std::vector<std::shared_ptr<Bullet>> & bullets, const State & state, sf::UdpSocket & socket); //thread
};