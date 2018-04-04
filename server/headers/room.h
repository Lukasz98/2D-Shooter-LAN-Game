#pragma once
#include <string>
#include <vector>
#include <thread>
//#include <memory>
#include <mutex>

#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>

#include "e_player.h"
#include "bullet.h"
#include "load_from_files.h"
#include "network_event.h"
#include "server_info.h"
#include "log.h"

enum State { RUNNING, STOP, PREPARATION };

class Room
{
public:
    Room(bool lanGame = true);
    ~Room();

    void SendData();
    void AddEvent(Event * event) { events.push_back(event); }
    void DeletePlayer(int i);

    inline const State & GetState() { return state; }
    std::vector<E_Player*> * GetPlayers() { return & ePlayers; }
    std::vector<Bullet*> * GetBullets() { return & bullets; }

    inline const std::string & GetMapName() { return mapName; }

    void Update();
    inline void A_TicketMinus(int m) { a_tickets -= m; }
    inline void B_TicketMinus(int m) { b_tickets -= m; }
    inline bool ZeroTickets() { if (a_tickets <= 0 || b_tickets <= 0) return true; return false; }
    inline void ResetTickets() { a_tickets = 100; b_tickets = 100; }
    
private:
    struct WaitForPlayersData
    {
        WaitForPlayersData() {}
        ~WaitForPlayersData() {}
        int receivePort;
        int * teamA, * teamB;
        std::string mapName;
    };
    WaitForPlayersData waitForPlayersData;

    std::string mapName = "testWorld";
    int teamA = 0, teamB = 0; // counting players in teams
    int a_tickets = 100, b_tickets = 100;

    std::vector<sf::Packet> packets;
    std::mutex packetsMutex;
X    int sendedPackets = 0;
    int packet_counter = 0; //received
    
    std::vector<E_Player*> ePlayers;
    std::vector<Bullet*> bullets;
    
    std::vector<Event*> events;

    State state = PREPARATION;
    ServerInfo info;
    sf::UdpSocket receiveSocket, sendSocket;
    sf::TcpListener tcpListener;
    
    void loadServerInfo();

    static void waitForPlayers(std::vector<E_Player*> & ePlayers, const State & state, sf::TcpListener & tcpListener, WaitForPlayersData & data); //thread
    static void receiveInput(std::vector<sf::Packet> & packets, const State & state, sf::UdpSocket & socket, std::mutex & packetsMutex);



    
};
