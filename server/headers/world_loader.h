#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <SFML/System/Vector2.hpp>

#include "world.h"
#include "log.h"

class WorldLoader
{
public:
    static World * LoadMap(std::string path);

private:
    static sf::Vector2i loadResp(std::fstream * file);
};

