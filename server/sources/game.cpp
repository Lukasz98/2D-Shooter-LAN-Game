#include "../headers/game.h"

Game::Game(Room * room)
{
    this->room = room;
    world = WorldLoader::LoadMap("../worlds/" + room->GetMapName());

    ePlayers = room->GetPlayers();
    bullets = room->GetBullets();

    play();
}

Game::~Game()
{
    delete world;
}


void Game::play()
{
    while (!kbhit() || room->GetState() != RUNNING)
    {
        room->Update();
        update();
     
        room->SendData();
        time.Update();
        //if (time.GetFpsTime() == 0.0f)
        //    LOG("FPS: " << time.GetFps());
    }
}

void Game::update()
{    
    for (auto ePlayer : *ePlayers)
    {
        ePlayer->SetDt(time.GetDt());
        world->TakeFlag(ePlayer);
    }

    for (size_t i = 0; i < ePlayers->size(); i++)
    {
        if ((*ePlayers)[i]->WasDead() == true)
        {
            int team = (*ePlayers)[i]->GetTeam();
            int ticketLoss = 1 + 1 * world->GetFlagFactor(team);

            if (team == NAZI)
                room->A_TicketMinus(ticketLoss);
            else
                room->B_TicketMinus(ticketLoss);
        }
      
        if ((*ePlayers)[i]->IsOnline() == false)
        {           
            PlayerDeleteEv * event = new PlayerDeleteEv((*ePlayers)[i]->GetId());
            room->AddEvent(event);
            room->DeletePlayer(i);
            break;
        }
    }

    for (size_t i = 0; i < bullets->size(); i++)
    {
        if ((*bullets)[i]->Update(time.GetDt()) == false)
        {
            BulletDeleteEv * event = new BulletDeleteEv((*bullets)[i]->GetOwnerId(), (*bullets)[i]->GetBulletId());
            room->AddEvent(event);
            delete (*bullets)[i];
            bullets->erase(bullets->begin() + i);
            break;
        }
    }

    if (room->ZeroTickets() == true)
    {
        time.UpdateGameOverTime();
        if (time.GetGameOverTime() > 10.0f)
        {
            for (auto p : *ePlayers)
                p->Damage(1000.0f); // kill them, so they respawn 

            room->ResetTickets();
            world->ResetFlags();
                
            time.ResetGameOverTime();
        }
    }
    
    updateFlags();
    collisions();
}

void Game::updateFlags()
{
    room->AddEvent(world->GetFlagsUpdateEv());
}

void Game::collisions()
{
    std::string map = world->GetMap();
    int mapW = world->GetMapWidth();
    int mapH = world->GetMapHeight();
    int tileW = 64.0f;

    
    for (auto player : *ePlayers)
    {
        if (world->IsBlocked(player))
            player->ReactOnCollision();
    }

    for (auto bullet : *bullets)
    {

        if (world->IsBlocked(bullet))
            bullet->CollisionReact(10.0f);

        for (auto player : *ePlayers)
        {
            bullet->Overlaps(player);
        }
    }

}
