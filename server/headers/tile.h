#pragma once
#include <memory>
#include "map_object.h"
#include "log.h"



class Tile : public MapObject
{
    bool isBlocking;
        
public:
    Tile() = delete;
    Tile(char type, int x, int y);
    ~Tile();

    inline int IsBlocking() { return isBlocking; } 

};
