#pragma once
#include <memory>
#include <string>
#include <thread>

#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>

#include "world.h"
#include "e_player.h"
#include "bullet.h"
#include "input_data.h"
#include "network_info.h"
#include "load_from_files.h"
#include "log.h"

class Connection
{
public:
    Connection(bool lanGame = true);
    ~Connection();

    void Update(World * world);
    void SendInput(Utils::InputData & input);
    void Close() { connected = false; }

    std::vector<E_Player*> * GetEPlayers() { return & ePlayers; }
    std::vector<Bullet*> * GetBullets() { return & bullets; }
    inline int GetMyId() { return myId; }
    inline const std::string & GetMapName() { return mapName; }
    inline bool isConnected() { return connected; }
    inline int GetNaziTickets() { return naziTickets; };
    inline int GetPolTickets() { return polTickets; };
    
    
private:
    int packet_counter = 0;
    
    bool connected = false;

    NetworkInfo info;
    
    //std::string serverIp = "192.168.1.14";
    int serverJoinPort, serverReceivingPort;
    //int serverReceivingPort;

    //std::string myIp = "192.168.1.14";
    //int myPort;
    int myId;

    std::vector<sf::Packet> receivedPackets;
    sf::UdpSocket receivingSocket, sendingSocket;

    std::string mapName;

    std::vector<E_Player*> ePlayers;
    std::vector<Bullet*> bullets;

    int naziTickets = 0, polTickets = 0;
    
    void joinServer();
    static void receiveData(std::vector<sf::Packet> & packets, sf::UdpSocket & socket, const bool & connected); //thread
    void updateEPlayers(sf::Packet & packet);
    void updateBullets(sf::Packet & packet);
    void updateEvents(sf::Packet & packet, World * world);

    enum EventType { UPDATE = 0, BULLET_DELETE = 1, PLAYER_DELETE = 2, FLAGS_UPDATE = 3 };
};
