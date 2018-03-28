#include "../headers/room.h"

Room::Room(bool lanGame)
{
    loadServerInfo();

    if (state == PREPARATION)
    {
        if (lanGame == true)
        {
            if (lanGame == true && receiveSocket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
                throw "Error binding receive socket";
        }
        else if (receiveSocket.bind(info.receivingPort) != sf::Socket::Done)
            throw "Error binding receive socket";

        info.receivingPort = receiveSocket.getLocalPort();
        receiveSocket.setBlocking(false);

        if (lanGame == true)
        {
            if (lanGame == true && sendSocket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
                throw "Error binding send socket";
        }
        else if (sendSocket.bind(info.sendingPort) != sf::Socket::Done)
            throw "Error binding send socket";
        
        info.sendingPort = sendSocket.getLocalPort();

        
        if (lanGame == true)
        {
            if (tcpListener.listen(sf::Socket::AnyPort) != sf::Socket::Done)
                throw "Error binding lan listener socket";
        }
        else if (tcpListener.listen(info.joinPort) != sf::Socket::Done)
            throw "Error binding listener socket";

        state = RUNNING;

        info.joinPort = tcpListener.getLocalPort();

        LOG("SERVER LAN IP: " << info.ip);
        LOG("SERVER JOIN TCP PORT: " << info.joinPort);
        
        waitForPlayersData.receivingPort = info.receivingPort;
        waitForPlayersData.mapName = mapName;
        waitForPlayersData.naziTeam = & naziTeam;
        waitForPlayersData.polTeam = & polTeam;

        std::thread (waitForPlayers, std::ref(ePlayers), std::ref(state), std::ref(tcpListener), std::ref(waitForPlayersData)).detach();
        std::thread (receiveInput, std::ref(packets), std::ref(state), std::ref(receiveSocket)).detach();
    }
    else
        throw "Room::Room - State stop";
}

Room::~Room() 
{
    LOG("Room::~Room packetsReceived="<<packet_counter);
    sendSocket.unbind();
}

void Room::loadServerInfo()
{
    try {
        info = LoadFromFiles::loadServerInfo();
        //LOG("LAN Server ip: " << ip);
        //LOG("Ethernet Server join port: " << joinPort);
    }
    catch (const char * err) {
        LOG(err);
        state = STOP;
        // TO DO
        // shutdown...
    }
}

void Room::waitForPlayers(std::vector<E_Player*> & ePlayers, const State & state, sf::TcpListener & tcpListener, WaitForPlayersData & data) //thread
{
    int id = 1;

    while (state == RUNNING)
    {
        sf::TcpSocket socket;
        if (tcpListener.accept(socket) != sf::Socket::Done)
        {
            LOG("Room:WaitForPlayers - TcpListener client acceptation error");
        }
        else
        {
            sf::Packet packet;
            socket.receive(packet);

            std::string clientIp;
            int clientPort;

            packet >> clientIp >> clientPort;

            int team = 1;
            if (*data.naziTeam > *data.polTeam)
            {
                team = 2;
                (*data.polTeam) ++;
            }
            else
            {
                (*data.naziTeam) ++;
            }

            ePlayers.push_back(new E_Player(id, clientIp, clientPort, team));
            sf::Vector2f pos = ePlayers.back()->GetPosition();

            sf::Packet packetToSend;
            packetToSend << data.mapName << data.receivingPort << id << team;
            packetToSend << pos.x << pos.y;
            socket.send(packetToSend);

            LOG("Player joined id=" << id << " ip=" << clientIp << " port=" << clientPort);
            id ++;
        }
    }

    tcpListener.close();
}

void Room::receiveInput(std::vector<sf::Packet> & packets, const State & state, sf::UdpSocket & socket)
{
    while (state == RUNNING)
    {
        sf::IpAddress clientIp;
        short unsigned int clientPort;
        sf::Packet packet;

        if (socket.receive(packet, clientIp, clientPort) == sf::Socket::Done)
            packets.push_back(packet);
    }
    socket.unbind();
}

void Room::Update()
{
    for (auto & packet : packets)
    {
        packet_counter ++;
        
        int id;
        sf::Vector2i dir;
        float angle;
        packet >> id >> dir.x >> dir.y >> angle;

        bool isCliced;
        packet >> isCliced;

        for (int i = 0; i < ePlayers.size(); i++)
        {
            if (ePlayers[i]->GetId() == id)
            {
                ePlayers[i]->Update(dir, angle);
                if (isCliced)
                {
                    int bulletId;
                    sf::Vector2f speedRatio;
                    packet >> speedRatio.x >> speedRatio.y >> bulletId;
                    bullets.push_back(new Bullet(ePlayers[i]->GetPosition(), speedRatio, id, bulletId));
                }
            }
        }
    }
    packets.clear();
}

void Room::SendData()
{
    sf::Packet packet;
    packet << naziTickets << polTickets;
    packet << (int)ePlayers.size();
    
    for (const auto player : ePlayers)
    {
        packet << player->GetId() << player->GetTeam() << player->GetPosition().x << player->GetPosition().y << player->GetAngle();
    }

    packet << (int)bullets.size();
    for (const auto bullet : bullets)
    {
        sf::Vector2f pos = bullet->GetPosition();
        sf::Vector2f speedRatio = bullet->GetSpeedRatio();
        packet << bullet->GetOwnerId() << bullet->GetBulletId() << pos.x << pos.y << speedRatio.x << speedRatio.y;
    }

    packet << (int)events.size();
    for (auto event : events)
    {
        event->PasteData(packet);
        delete event;
    }
    events.clear();


    for (const auto player : ePlayers)
    {
        sendSocket.send(packet, player->GetIp(), player->GetPort());
    }

}

void Room::DeletePlayer(int i)
{
    LOG("Room::DeletePlayer ip="<<ePlayers[i]->GetId()<<", ip="<<ePlayers[i]->GetIp()<<", port="<<ePlayers[i]->GetPort());
    if (ePlayers[i]->GetTeam() == 1)
        naziTeam--;
    else
        polTeam--;
    delete ePlayers[i];
    ePlayers.erase(ePlayers.begin() + i);
}
