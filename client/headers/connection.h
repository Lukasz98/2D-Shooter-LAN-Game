#pragma once
#include <string>
#include <thread>
#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>
#include "e_player.h"
#include "bullet.h"
#include "user_input.h"
#include "log.h"

class Connection
{
public:
	Connection();
	~Connection();

	inline bool isConnected() { return connected; }
	void SendInput(Game::InputData & input);
	void Close() { connected = false; }

	std::vector<E_Player*> * GetEPlayers() { return & ePlayers; }
	std::vector<Bullet*> * GetBullets() { return & bullets; }
	int GetMyId() { return myId; }

private:
	bool connected = false;
	std::string serverIp = "192.168.1.109";
	int serverJoinPort, serverReceivingPort, serverSendingPort; // serverSendingPort not used propably

	std::string myIp = "192.168.1.109";
	int myPort;
	int myId;

	sf::UdpSocket receivingSocket, sendingSocket;

//	sf::UdpSocket udpSocket;

	std::vector<E_Player*> ePlayers;
	std::vector<Bullet*> bullets;


	void joinServer();
	static void receiveData(std::vector<E_Player*> & ePlayers, std::vector<Bullet*> & bullets, sf::UdpSocket & socket, const bool & connected, int myPort); //thread //myPort not needed anymore

};