#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include "world.h"
#include "floor.h"
#include "wall.h"
#include "log.h"

class WorldLoader
{
public:
	static World * LoadMap(const char *_path);


private:
	static Floor * loadFloor(std::fstream * _file);
	static Wall * loadWall(std::fstream * _file);
};

