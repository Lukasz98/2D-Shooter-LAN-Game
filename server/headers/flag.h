#pragma once
#include "tile.h"
#include "log.h"


#define NONE 0
#define NAZI 1
#define POL 2

class Flag : public Tile
{
    char id;
    int owner = NONE;
    int isTaking = NONE;
    float neutral = 0.0f, last = 0.0f;
    float speed = 0.5f;

public:
    Flag(char id, int x, int y);
    ~Flag();

    void Take(int side);

    inline const int GetId() { return id; }
    inline const int GetOwner() { return owner; }
    inline const int GetIsTaker() { return isTaking; }
    inline const int GetNeutralPoints() { return neutral; }
    inline const int GetLastPoints() { return last; }
    
};
