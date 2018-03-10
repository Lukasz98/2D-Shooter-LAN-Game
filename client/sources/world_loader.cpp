#include "../headers/world_loader.h"


World * WorldLoader::LoadMap(std::string path)
{
    World * world = new World();

    std::fstream * file = new std::fstream(path);

    if (file->is_open())
    {
        std::string check;
        int mapW = 0, mapH = 0;
        std::string map;

        *file >> mapW >> mapH;

        for (int i = 0; i < mapH; i++)
        {
            std::string row;
            *file >> check; // going on row number
            *file >> row;
            map += row;
        }

        while (!file->eof())
        {
            *file >> check;
        }

        file->close();

        world->SetMap(map, mapW, mapH);
    }

    delete file;
    return world;
}


