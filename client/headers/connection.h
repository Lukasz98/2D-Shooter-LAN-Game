#pragma once
#include <memory>
#include <string>
#include <thread>

#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>

#include "e_player.h"
#include "bullet.h"
#include "input_data.h"
#include "log.h"

class Connection
{
public:
	Connection();
	~Connection();

	void Update();
	void SendInput(Utils::InputData & input);
	void Close() { connected = false; }

	std::vector<std::shared_ptr<E_Player>> * GetEPlayers() { return & ePlayers; }
	std::vector<Bullet*> * GetBullets() { return & bullets; }
	inline const int & GetMyId() { return myId; }
	inline const std::string & GetMapName() { return mapName; }
	inline const bool & isConnected() { return connected; }

private:
	bool connected = false;
	std::string serverIp = "192.168.1.12";
	int serverJoinPort, serverReceivingPort;

	std::string myIp = "192.168.1.12";
	int myPort;
	int myId;

	std::vector<sf::Packet> receivedPackets;
	sf::UdpSocket receivingSocket, sendingSocket;

	std::string mapName;

	std::vector<std::shared_ptr<E_Player>> ePlayers;
	std::vector<Bullet*> bullets;

	void joinServer();
	static void receiveData(std::vector<sf::Packet> & packets, sf::UdpSocket & socket, const bool & connected); //thread
	void updateEPlayers(sf::Packet & packet);
	void updateBullets(sf::Packet & packet);
	void updateEvents(sf::Packet & packet);
	enum EventType { UPDATE = 0, BULLET_DELETE = 1, PLAYER_DELETE = 2, TITS_UPDATE = 3 };
};