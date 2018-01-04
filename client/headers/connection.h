#pragma once
#include <string>
#include <thread>
#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>
#include "e_player.h"
#include "log.h"


#include "math_calc.h" //for userInput only
// this struct have to be in another file
struct UserInput
{
	int x = 0, y = 0;
	float angle = 0.0f;
	void reset() { x = 0; y = 0;}

	void updateMousePos(sf::Vector2i mousePos)
	{
		sf::Vector2f pos(1280.0f /2.0f, 720.0f / 2.0f);
		sf::Vector2f mp((float) mousePos.x, (float) mousePos.y);
		angle = Math_calc::GetAngle(pos, mp);
	}
};

class Connection
{
public:
	Connection();
	~Connection();

	inline bool isConnected() { return connected; }
	void SendInput(UserInput & input);
	void Close() { connected = false; }

	std::vector<E_Player*> & GetEPlayers() { return ePlayers; }
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


	void joinServer();
	static void receiveData(std::vector<E_Player*> & ePlayers, sf::UdpSocket & socket, const bool & connected, int myPort); //thread //myPort not needed anymore

};