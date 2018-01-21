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
				world->AddFloor(loadFloor(file));

			if (check == "wall")
				world->AddWall(loadWall(file));

			if (check == "redResp")
				world->SetRedResp(loadResp(file));

			if (check == "whiteResp")
				world->SetWhiteResp(loadResp(file));

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
		*file >> check;
	}

	floor->SetPosition(sf::Vector2f(x, y));
	floor->SetSize(sf::Vector2f(width, height));

	return floor;
}

Wall * WorldLoader::loadWall(std::fstream * file)
{
	Wall * wall = new Wall();

	std::string check("");
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
		*file >> check;
	}

	wall->SetPosition(sf::Vector2f(x, y));
	wall->SetSize(sf::Vector2f(width, height));

	return wall;
}

sf::Vector2f WorldLoader::loadResp(std::fstream * file)
{
	sf::Vector2f result;
	
	std::string check("");
	*file >> check; // going on braces
	*file >> check; // going on x
	while (check != "}")
	{
		if (check == "x:")
			*file >> result.x;
		if (check == "y:")
			*file >> result.y;

		*file >> check;
	}
	
	return result;
}
