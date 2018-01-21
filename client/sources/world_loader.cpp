#include "../headers/world_loader.h"


World * WorldLoader::LoadMap(std::string path)
{
	World * world = new World();

	std::fstream * file = new std::fstream(path);

	if (file->is_open())
	{
		std::string check;
		while (!file->eof())
		{
			*file >> check;

			if (check == "floor")
			{
				world->AddFloor(loadFloor(file));
			}

			if (check == "wall")
			{
				world->AddWall(loadWall(file));
			}
		}
		file->close();
	}

	delete file;
	return world;
}

Floor * WorldLoader::loadFloor(std::fstream * file)
{
	Floor * floor = new Floor();

	std::string check("");
	std::string texturePath;
	float x = 0, y = 0, width = 0, height = 0;

	*file >> check; // going on braces
	*file >> check; // going on x
	while (check != "}")
	{
		if (check == "x:")
			*file >> x;
		if (check == "y:")
			*file >> y;
		if (check == "width:")
			*file >> width;
		if (check == "height:")
			*file >> height;
		if (check == "texture:")
			*file >> texturePath;
		*file >> check;
	}

	floor->SetPosition(sf::Vector2f(x, y));
	floor->SetSize(sf::Vector2f(width, height));
	floor->SetTexture(texturePath);

	return floor;
}

Wall * WorldLoader::loadWall(std::fstream * file)
{
	Wall * wall = new Wall();

	std::string check("");
	std::string texturePath;
	float x = 0, y = 0, width = 0, height = 0;

	*file >> check; // going on braces
	*file >> check; // going on x
	while (check != "}")
	{
		if (check == "x:")
			*file >> x;
		if (check == "y:")
			*file >> y;
		if (check == "width:")
			*file >> width;
		if (check == "height:")
			*file >> height;
		if (check == "texture:")
			*file >> texturePath;
		*file >> check;
	}

	wall->SetPosition(sf::Vector2f(x, y));
	wall->SetSize(sf::Vector2f(width, height));
	wall->SetTexture(texturePath);

	return wall;
}


