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
    inline int GetMapWidth() { return mapW; }
    inline int GetMapHeight() { return mapH; }
    inline const std::string & GetMap() { return map; }

    void SetMap(std::string map, int mapW, int mapH);

    void SetRedResp(sf::Vector2i pos);
    void SetWhiteResp(sf::Vector2i pos);
    
    bool IsBlocked(const std::shared_ptr<Entity> body);

    void TakeFlag(const std::shared_ptr<E_Player> body);

    FlagsUpdateEv * GetFlagsUpdateEv();
    int GetFlagFactor(int team);
    void ResetFlags();
    
private:
    std::vector<Tile> tiles;
    std::vector<Flag> flags;
    std::string map;
    int mapW, mapH;
    int tileW = 64.0f;

    sf::Vector2f redResp, whiteResp;

}; 
