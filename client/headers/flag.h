#pragma once

#include <string>
#include "tile.h"
#include "log.h"

#define NONE 0
#define NAZI 1
#define POL 2

class Flag : public Tile
{
    int id, owner, isTaking;
    std::string id_c;
    float neutral, last;
    std::string texturePath_n;
    sf::Texture naziT, polT, partlyTaken;

public:
    Flag(float x, float y, float w, int id);
    ~Flag();

    inline int GetId() { return id; }
    
    void SetOwner(int o);
    void SetIsTaker(int o);    
    void SetNeutralPoints(int n) { neutral = n; }
    void SetLastPoints(int l) { last = l; }
};
