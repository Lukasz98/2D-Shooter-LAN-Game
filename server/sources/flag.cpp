#include "../headers/flag.h"


Flag::Flag(char id, int x, int y)
: Tile(id, x, y)
{
    this->id = id;
}

Flag::~Flag()
{

}

void Flag::Take(int side)
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
    if (neutral > 100.0f) neutral = 100.0f;

    if (last < 0.0f) last = 0.0f;
    if (last > 100.0f) last = 100.0f;

    if (last == 100.0f) owner = isTaking;
    if (owner != NONE && last == 0.0f) owner = NONE;
    if (neutral == 0.0f) isTaking = NONE;
}

void Flag::Reset()
{
    owner = NONE;
    isTaking = NONE;
    neutral = 0.0f;
    last = 0.0f;
}
