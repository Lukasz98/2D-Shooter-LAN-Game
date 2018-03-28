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
    inline void NaziTicketMinus(int m) { naziTickets -= m; }
    inline void PolTicketMinus(int m) { polTickets -= m; }
    inline bool ZeroTickets() { if (naziTickets <= 0 || polTickets <= 0) return true; return false; }
    inline void ResetTickets() { naziTickets = 100; polTickets = 100; }

    
private:
    struct WaitForPlayersData
    {
        WaitForPlayersData() {}
        ~WaitForPlayersData() {}
        int receivingPort;
        int * naziTeam, * polTeam;
        std::string mapName;
    };

    int packet_counter = 0;
    std::vector<sf::Packet> packets;
    
    std::string mapName = "testWorld";

    int naziTeam = 0, polTeam = 0; // counting players in teams
    int naziTickets = 10, polTickets = 100;
   
    std::vector<E_Player*> ePlayers;
    std::vector<Bullet*> bullets;
    
    std::vector<Event*> events;

    //std::string ip;
    //int joinPort, receivingPort, sendingPort;
    ServerInfo info;
    sf::UdpSocket receiveSocket, sendSocket;

    State state = PREPARATION;

    sf::TcpListener tcpListener;

    WaitForPlayersData waitForPlayersData;

    void loadServerInfo();

    static void waitForPlayers(std::vector<E_Player*> & ePlayers, const State & state, sf::TcpListener & tcpListener, WaitForPlayersData & data); //thread
    static void receiveInput(std::vector<sf::Packet> & packets, const State & state, sf::UdpSocket & socket);



    
};
