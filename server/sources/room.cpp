#include "../headers/room.h"

Room::Room()
{
    loadServerInfo();

    if (state == PREPARATION)
    {
        receiveSocket.bind(sf::Socket::AnyPort);
        receivingPort = receiveSocket.getLocalPort();
        receiveSocket.setBlocking(false);

        sendSocket.bind(sf::Socket::AnyPort);
        sendingPort = sendSocket.getLocalPort();


        if (tcpListener.listen(sf::Socket::AnyPort) != sf::Socket::Done)
        {
            LOG("Room:WaitForPlayers - TcpListener error");
            //do something
            return;
        }

        state = RUNNING;

        joinPort = tcpListener.getLocalPort();
        LOG("SERVER JOIN TCP PORT: " << joinPort);

        waitForPlayersData.receivingPort = receivingPort;
        waitForPlayersData.mapName = mapName;
        waitForPlayersData.naziTeam = & naziTeam;
        waitForPlayersData.polTeam = & polTeam;

        std::thread (waitForPlayers, std::ref(ePlayers), std::ref(state), std::ref(tcpListener), std::ref(waitForPlayersData)).detach();
        std::thread (receiveInput, std::ref(packets), std::ref(state), std::ref(receiveSocket)).detach();
    }
}

Room::~Room() 
{
    LOG("Room::~Room packetReceived="<<packet_counter);
    sendSocket.unbind();
}

void Room::loadServerInfo()
{
    try {
        LoadFromFiles::loadServerInfo(ip, joinPort);
        LOG("Server ip: " << ip);
        LOG("Server join port: " << joinPort);
    }
    catch (const char * err) {
        LOG(err);
        state = STOP;
        // TO DO
        // shutdown...
    }
}

void Room::waitForPlayers(std::vector<std::shared_ptr<E_Player>> & ePlayers, const State & state, sf::TcpListener & tcpListener, WaitForPlayersData & waitForPlayersData) //thread
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
            if (*waitForPlayersData.naziTeam > *waitForPlayersData.polTeam)
            {
                team = 2;
                (*waitForPlayersData.polTeam) ++;
            }
            else
            {
                (*waitForPlayersData.naziTeam) ++;
            }

            ePlayers.push_back(std::make_shared<E_Player>(id, clientIp, clientPort, team));
            sf::Vector2f pos = ePlayers.back()->GetPosition();

            sf::Packet packetToSend;
            packetToSend << waitForPlayersData.mapName << waitForPlayersData.receivingPort << id << team;
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
                    bullets.push_back(std::make_shared<Bullet>(ePlayers[i]->GetPosition(), speedRatio, id, bulletId));
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
    
    for (auto player : ePlayers)
    {
        packet << player->GetId() << player->GetTeam() << player->GetPosition().x << player->GetPosition().y << player->GetAngle();
    }

    packet << (int)bullets.size();
    for (auto bullet : bullets)
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


    for (auto player : ePlayers)
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
    ePlayers.erase(ePlayers.begin() + i);
}
