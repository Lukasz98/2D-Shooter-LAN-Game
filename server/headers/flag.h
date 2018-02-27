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
    Flag(char id, int x, int y)
    : Tile(id, x, y)
    {
        this->id = id;
    }
    ~Flag() {}

    void Take(int side)
    {
        if (side == NAZI)
        { 
            if (isTaking == POL)
            {       
                if (neutral < 100.0f || last == 0.0f) neutral -= speed * 2.0f;
                else if (last > 0.0f) last -= speed;
            }
            else if (isTaking == NAZI)
            {
                if (neutral < 100.0f) neutral += speed * 2.0f;
                else if (last < 100.0f) last += speed;
            }
            else if (isTaking == NONE)
            {
                isTaking = NAZI;
                neutral += speed * 2.0f;
            }
        }
        else if (side == POL)
        {                                                        
            if (isTaking == NAZI)                                
            {
                if (neutral < 100.0f || last == 0.0f) neutral -= speed * 2.0f;
                else if (last > 0.0f) last -= speed;
            }
            else if (isTaking == POL)
            {
                if (neutral < 100.0f) neutral += speed * 2.0f;
                else if (last < 100.0f) last += speed;
            }
            else if (isTaking == NONE)
            {
                isTaking = POL;
                neutral += speed * 2.0f;
            }
        }

        if (neutral < 0.0f) neutral = 0.0f;
        if (neutral > 100.0f)
        {
            neutral = 100.0f;
        }
        if (last < 0.0f) last = 0.0f;
        if (last > 100.0f) last = 100.0f;

        if (last == 100.0f) owner = isTaking;
        if (owner != NONE && last == 0.0f) owner = NONE;
        if (neutral == 0.0f) isTaking = NONE;

        //LOG("owner="<<owner << ", " << "isTaking="<<isTaking << ", " << "neutral="<<neutral << ", " << "last="<<last);
    }

    inline const int GetId() { return id; }
    inline const int GetOwner() { return owner; }
    inline const int GetIsTaker() { return isTaking; }
    inline const int GetNeutralPoints() { return neutral; }
    inline const int GetLastPoints() { return last; }
    
};

