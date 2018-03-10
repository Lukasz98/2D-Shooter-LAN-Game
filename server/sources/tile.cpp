#include "../headers/tile.h"


Tile::Tile(char type, int x, int y)
{
    if (type == 'w' || type == 'z')
        isBlocking = true;
    else
        isBlocking = false;

    size.x = 64.0f;
    size.y = 64.0f;
    pos.x = size.x * x;
    pos.y = size.y * y; 
}

Tile::~Tile()
{

}
