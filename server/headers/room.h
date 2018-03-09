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
#include "network_event.h"

enum State { RUNNING, STOP, PREPARATION };

struct WaitForPlayersData
{
	WaitForPlayersData() {}
	~WaitForPlayersData() {}
	int receivingPort;
	int * naziTeam, * polTeam;
	std::string mapName;
};

class Room
{
public:
	Room();
	~Room();

	void SendData();
	void AddEvent(Event * event) { events.push_back(event); }
	void DeletePlayer(int i);

	inline const State & GetState() { return state; }
	std::vector<std::shared_ptr<E_Player>> * GetPlayers() { return & ePlayers; }
	std::vector<std::shared_ptr<Bullet>> * GetBullets() { return & bullets; }

	inline const std::string & GetMapName() { return mapName; }

	void Update();
	void NaziTicketMinus(int m) { naziTickets -= m; }
	void PolTicketMinus(int m) { polTickets -= m; }
	
	
private:
	int packet_counter = 0;
	std::vector<sf::Packet> packets;
	
	std::string mapName = "testWorld";

	int naziTeam = 0, polTeam = 0; // counting players in teams
	int naziTickets = 100, polTickets = 100;
   
	std::vector<std::shared_ptr<E_Player>> ePlayers;
	std::vector<std::shared_ptr<Bullet>> bullets;
	
	std::vector<Event*> events;

	std::string ip;
	int joinPort, receivingPort, sendingPort;
	sf::UdpSocket receiveSocket, sendSocket;

	State state = PREPARATION;

	sf::TcpListener tcpListener;

	WaitForPlayersData waitForPlayersData;

	void loadServerInfo();

	static void waitForPlayers(std::vector<std::shared_ptr<E_Player>> & ePlayers, const State & state, sf::TcpListener & tcpListener, WaitForPlayersData & waitForPlayersData); //thread
	//static void receiveInput(std::vector<std::shared_ptr<E_Player>> & ePlayers, std::vector<std::shared_ptr<Bullet>> & bullets, const State & state, sf::UdpSocket & socket, int & counter); //thread

	static void receiveInput(std::vector<sf::Packet> & packets, const State & state, sf::UdpSocket & socket);
};
