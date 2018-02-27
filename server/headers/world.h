#pragma once
#include <memory>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>


#include "body.h"

#include "e_player.h"
#include "bullet.h"
#include "wall.h"
#include "floor.h"
#include "tile.h"
#include "flag.h"
#include "log.h"
#include "network_event.h"


class World
{
public:
	World();
	~World();

	void Update(float dt);
    inline const int & GetMapWidth() { return mapW; }
    inline const int & GetMapHeight() { return mapH; }
    inline const std::string & GetMap() { return map; }
    //const std::vector<Tile*> * GetTiles() { return & tiles; }

    void SetMap(std::string map, int mapW, int mapH) {
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


    void SetRedResp(sf::Vector2i pos) 
    { 
        redResp.x = pos.x * tileW - tileW / 2.0f; 
        redResp.y = pos.y * tileW - tileW / 2.0f; 
        Body::RED_RESP = redResp; 
    }
	void SetWhiteResp(sf::Vector2i pos) 
    { 
        whiteResp.x = pos.x * tileW; 
        whiteResp.y = pos.y * tileW; 
        Body::WHITE_RESP = whiteResp; 
    }

    bool IsBlocked(const std::shared_ptr<Entity> body)
    {
        
        for (auto & tile : tiles) 
            if  (tile.IsBlocking() && tile.Overlaps(body))
                return true;

        return false;
    }

    void TakeFlag(const std::shared_ptr<E_Player> body)
    {
        sf::Vector2f pos = body->GetPosition();

        for (auto & flag : flags)
        {
            sf::Vector2f fpos = flag.GetPosition();
            //LOG(pos.x << ", " << fpos.x << ", " << fpos.y);
            if (Math_calc::GetLength(pos, fpos) < 500.0f)
            {
                flag.Take(body->GetTeam());
                //LOG("World::takeFlag");
            }
        }
    }

    FlagsUpdateEv * GetFlagsUpdateEv()
    {
        FlagsUpdateEv * ev = new FlagsUpdateEv();
        for (auto & f : flags)
        {
            ev->AddData(f.GetId(), f.GetOwner(), f.GetIsTaker(), f.GetNeutralPoints(), f.GetLastPoints());
            //break;
        }
        return ev;
    }


private:
    std::vector<Tile> tiles;
    std::vector<Flag> flags;
    std::string map;
    int mapW, mapH;
    int tileW = 64.0f;

	sf::Vector2f redResp, whiteResp;

}; 
