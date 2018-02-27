#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "log.h"


class Tile : public sf::RectangleShape
{
public:
	Tile(std::string path, float x, float y, float s)
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
	~Tile() {}

public:
	sf::Vector2f pos;
    float size;
	sf::Texture texture;
};

