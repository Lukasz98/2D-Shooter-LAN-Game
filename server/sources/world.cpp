#include "../headers/world.h"


World::World()
{

}

World::~World()
{
//  for(size_t i = 0; i < tiles.size(); i++)
//    delete tiles[i];
}

void World::Update(float dt)
{

}

void World::SetMap(std::string map, int mapW, int mapH)
{
    this->map = map;
    this->mapW = mapW;
    this->mapH = mapH;
    
    for (int y = 0; y < mapH; y++)
    {
        for (int x = 0; x < mapW; x++)
        {
            int id = x + y + (mapW - 1) * y;
            if (map[id] == 'A' || map[id] == 'B' || map[id] == 'C')
                flags.push_back(Flag(map[id], x, y));
            else
                tiles.push_back(Tile(map[id], x, y));
        }
    }
}

void World::SetRedResp(sf::Vector2i pos) 
{ 
    redResp.x = pos.x * tileW - tileW / 2.0f; 
    redResp.y = pos.y * tileW - tileW / 2.0f; 
    Body::RED_RESP = redResp; 
}

void World::SetWhiteResp(sf::Vector2i pos) 
{ 
    whiteResp.x = pos.x * tileW; 
    whiteResp.y = pos.y * tileW; 
    Body::WHITE_RESP = whiteResp; 
}

bool World::IsBlocked(const std::shared_ptr<Entity> body)
{    
    for (auto & tile : tiles) 
        if  (tile.IsBlocking() && tile.Overlaps(body))
            return true;

    return false;
}

void World::TakeFlag(const std::shared_ptr<E_Player> body)
{
    sf::Vector2f pos = body->GetPosition();

    for (auto & flag : flags)
    {
        sf::Vector2f fpos = flag.GetPosition();
        if (Math_calc::GetLength(pos, fpos) < 500.0f)
        {
            flag.Take(body->GetTeam());
        }
    }
}

FlagsUpdateEv * World::GetFlagsUpdateEv()
{
    FlagsUpdateEv * ev = new FlagsUpdateEv();
    for (auto & f : flags)
        ev->AddData(f.GetId(), f.GetOwner(), f.GetIsTaker(), f.GetNeutralPoints(), f.GetLastPoints());

    return ev;
}

int World::GetFlagFactor(int team)
{
    int factor = 0;
    for (auto & f : flags)
    {
        int o = f.GetOwner();
        if (o != team && o != NONE)
            factor++;
    }

    return factor;
}


