#include "../headers/tile.h"


Tile::Tile(std::string path, float x, float y, float s)
{
    setPosition(sf::Vector2f(x, y));
    pos.x = x; 
    pos.y = y;
    this->size = s;
    setSize(sf::Vector2f(size, size));
    
    if (path != "")
    {
        texture.loadFromFile(path);
        setTexture(&texture);   
    }
}

Tile::~Tile()
{
}
