#pragma once
#include <memory>
#include "map_object.h"
#include "log.h"



class Tile : public MapObject
{
    bool isBlocking;
        
public:
    Tile() = delete;
    Tile(char type, int x, int y)
    {
    //LOG("new Tile"<<x<<y);
        if (type == 'w' || type == 'z')
            isBlocking = true;
        else
            isBlocking = false;

        size.x = 64.0f;
        size.y = 64.0f;
        pos.x = size.x * x;
        pos.y = size.y * y; 
   }

    ~Tile() {}


    inline int IsBlocking() { return isBlocking; } 

};

