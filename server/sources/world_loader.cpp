#include "../headers/world_loader.h"


World * WorldLoader::LoadMap(std::string _path)
{
//LOG("WorldLoader::LoadMap");
	World * world = new World();

	std::fstream * file = new std::fstream(_path);

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

Floor * WorldLoader::loadFloor(std::fstream * _file)
{
	Floor * floor = new Floor();

	std::string check("");
//	std::string texturePath;
	float x = 0, y = 0, width = 0, height = 0;

	*_file >> check; // going on braces
	*_file >> check; // going on x
	while (check != "}")
	{
		if (check == "x:")
			*_file >> x;
		if (check == "y:")
			*_file >> y;
		if (check == "width:")
			*_file >> width;
		if (check == "height:")
			*_file >> height;
//		if (check == "texture:")
//			*_file >> texturePath;
		*_file >> check;
	}

	floor->m_SetPosition(sf::Vector2f(x, y));
	floor->m_SetSize(sf::Vector2f(width, height));
//	floor->m_SetTexture(texturePath);

	return floor;
}

Wall * WorldLoader::loadWall(std::fstream * _file)
{
	Wall * wall = new Wall();

	std::string check("");
//	std::string texturePath;
	float x = 0, y = 0, width = 0, height = 0;

	*_file >> check; // going on braces
	*_file >> check; // going on x
	while (check != "}")
	{
		if (check == "x:")
			*_file >> x;
		if (check == "y:")
			*_file >> y;
		if (check == "width:")
			*_file >> width;
		if (check == "height:")
			*_file >> height;
//		if (check == "texture:")
//			*_file >> texturePath;
		*_file >> check;
	}

	wall->m_SetPosition(sf::Vector2f(x, y));
	wall->m_SetSize(sf::Vector2f(width, height));
//	wall->m_SetTexture(texturePath);

	return wall;
}

sf::Vector2f WorldLoader::loadResp(std::fstream * _file)
{
	sf::Vector2f result;
	
	std::string check("");
	*_file >> check; // going on braces
	*_file >> check; // going on x
	while (check != "}")
	{
		if (check == "x:")
			*_file >> result.x;
		if (check == "y:")
			*_file >> result.y;

		*_file >> check;
	}
	
	return result;
}
