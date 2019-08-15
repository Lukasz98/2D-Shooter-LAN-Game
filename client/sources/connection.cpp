#include "../headers/connection.h"


Connection::Connection(bool lanGame)
{
    LOG("Podaj port servera: ");
    std::cin >> serverJoinPort;

    try
    {
        info = LoadFromFiles::LoadNetworkInfo();
    }
    catch (const char * e)
    {
        throw e;
    }
    
    if (lanGame == true)
    {
        if (receivingSocket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
            throw "Receive socket bind error";
    }
    else if (receivingSocket.bind(info.myPort) != sf::Socket::Done)
        throw "Receive socket bind error";
    
    receivingSocket.setBlocking(false);
    info.myPort = receivingSocket.getLocalPort();
    LOG("My port=" << info.myPort);

    joinServer();

    if (connected)
    {
        std::thread (receiveData, std::ref(receivedPackets), std::ref(receivingSocket), std::ref(connected), std::ref(packetsMutex)).detach();
        LOG("Connection: receiveData started");

        LOG("Connection: Constructor - binding sendingSocket");
        if (lanGame == true)
        {
            if (sendingSocket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
                throw "Send socket bind error";
        }
        else if (sendingSocket.bind(info.sendPort) != sf::Socket::Done)
            throw "Send socket bind error";
    }
}

Connection::~Connection() 
{
    LOG("Connection::~Connection sendedPackets=" << packet_counter);
    LOG("Connection::~Connection receivedPackets=" << recPackets);
    sendingSocket.unbind();
    for (auto ePlayer : ePlayers)
        delete ePlayer;
    for (auto bullet : bullets)
        delete bullet;
}

void Connection::joinServer()
{
    sf::TcpSocket tcpSocket;
    if (tcpSocket.connect(info.serverIp, serverJoinPort) != sf::Socket::Done)
    {
        // throw exc
        LOG("Connection:joinServer - cannot connect to server");
    }
    else
    {
        sf::Packet myPacket;
        myPacket << info.myIp << info.myPort;
        tcpSocket.send(myPacket);

        sf::Packet serverPacket;
        tcpSocket.receive(serverPacket);

        int team = 1;
        serverPacket >> mapName >> serverReceivingPort >> myId >> team;

        sf::Vector2f pos;
        serverPacket >> pos.x >> pos.y;
        ePlayers.push_back(new E_Player(myId, pos, team));

        tcpSocket.disconnect();

        LOG("Welcome");
        connected = true;
    }

}

void Connection::receiveData(std::vector<sf::Packet> & packets, sf::UdpSocket & socket, const bool & connected, std::mutex & packetsMutex) //thread
{
    LOG("Connection: receiveData start");
    while (connected)
    {
        sf::IpAddress servIp;
        unsigned short servPort;
        sf::Packet packet;

        if (socket.receive(packet, servIp, servPort) == sf::Socket::Done)
        {
            packetsMutex.lock();
            packets.push_back(packet);
            packetsMutex.unlock();
        }
    }
    socket.unbind();    
}

void Connection::SendInput(Utils::InputData & input)
{
    sf::Packet packet;
    packet << myId << input.x << input.y << input.angle << input.mouseClick;
    if (input.mouseClick)
        packet << input.speedRatio.x << input.speedRatio.y << input.bulletId;

    sendingSocket.send(packet, info.serverIp, serverReceivingPort);
    packet_counter ++;
}

void Connection::Update(World * world)
{    
    int localCounter = 0;
    packetsMutex.lock();
    int packetsCount = receivedPackets.size();
    //LOG("size: "<<receivedPackets.size());
    for (auto & packet : receivedPackets)
    {
        sf::Packet p = packet;
        packetsMutex.unlock();

        int nr;
        p >> nr;
        //LOG("Packet nr: " << nr);
        
        localCounter++;
        recPackets ++;
        //packet_counter++;

        //packet >> naziTickets >> polTickets;
        p >> naziTickets >> polTickets;

        //updateEPlayers(packet);
        //updateBullets(packet);
        //updateEvents(packet, world);
        updateEPlayers(p);
        updateBullets(p);
        updateEvents(p, world);

        packetsMutex.lock();
    }
    for (int i = 0; i < localCounter; i++)
        receivedPackets.erase(receivedPackets.begin());
    //receivedPackets.clear();
    packetsMutex.unlock();
    
    //if (localCounter != 1)
    //LOG("Packets received in this frame: " << localCounter);
}

void Connection::updateEPlayers(sf::Packet & packet)
{
    int playersCount = 0;
    packet >> playersCount;
    
    for (int j = 0; j < playersCount; j++)
    {
        int id, team;
        float angle;
        sf::Vector2f pos;
        packet >> id >> team >> pos.x >> pos.y >> angle;

        bool do_i_know_this_guy = false;
        for (auto ePlayer : ePlayers)
        {
            if (ePlayer->GetId() == id)
            {
                ePlayer->Update(pos, angle);
                do_i_know_this_guy = true;
            }
        }
        
        if (do_i_know_this_guy == false)
        {
            ePlayers.push_back(new E_Player(id, pos, team));
        }
    }
}

void Connection::updateBullets(sf::Packet & packet)
{
    int bulletCount = 0;
    packet >> bulletCount;

    for (int j = 0; j < bulletCount; j++)
    {
        int ownerId, bulletId;
        sf::Vector2f pos, speedRatio;
        packet >> ownerId >> bulletId >> pos.x >> pos.y >> speedRatio.x >> speedRatio.y;

        bool do_i_know_this_bullet = false;
        for (auto bullet : bullets)
        {
            if (bullet->GetOwnerId() == ownerId && bullet->GetBulletId() == bulletId)
            {
                bullet->SetPosition(pos);
                do_i_know_this_bullet = true;
            }
        }   

        if (do_i_know_this_bullet == false)
        {
            bullets.push_back(new Bullet(pos, speedRatio, ownerId, bulletId));
        }
    }
}

void Connection::updateEvents(sf::Packet & packet, World * world)
{
    int eventsCount = 0;
    packet >> eventsCount;

    for (int i = 0; i < eventsCount; i++)
    {
        int t = -1;
        packet >> t;
        EventType type = static_cast<EventType> (t);

        switch (type)
        {
            case BULLET_DELETE:
            {
                int ownerId = 0, id = 0;
                packet >> ownerId >> id;
                for (int b = 0; b < bullets.size(); b++)
                    if (bullets[b]->GetOwnerId() == ownerId && bullets[b]->GetBulletId() == id)
                    {
                        delete bullets[b];
                        bullets.erase(bullets.begin() + b);
                        break;
                    }
                break;
            }
            case PLAYER_DELETE:
            {   
                int playerId = 0;
                packet >> playerId;
                for (int p = 0; p < ePlayers.size(); p++)
                    if (ePlayers[p]->GetId() == playerId)
                    {
                        delete ePlayers[p];
                        ePlayers.erase(ePlayers.begin() + p);
                        break;
                    }
                break;
            }
            case FLAGS_UPDATE:
            {
                int flagCount = 0;
                packet >> flagCount;
                for (int i = 0; i < flagCount; i++)
                {
                    int id, owner, isTaker;
                    float neutralPoints, lastPoints;
                    packet >> id >> owner >> isTaker >> neutralPoints >> lastPoints;
                    world->UpdateFlag(id, owner, isTaker, neutralPoints, lastPoints);
                }
                break;
            }
            default:
            {
                LOG("Error: Packet type = " << (int)type);
            }
        }
    }
}

