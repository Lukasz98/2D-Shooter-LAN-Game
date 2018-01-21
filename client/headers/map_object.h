#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "body.h"
#include "log.h"


class MapObject : public sf::RectangleShape
{
public:
	MapObject();
	~MapObject();

	void SetPosition(sf::Vector2f pos);
	void SetSize(sf::Vector2f size);
	void SetTexture(std::string path);

	bool Overlaps(const Body * body);

protected:
	sf::Vector2f pos, size;
	sf::Texture texture;
};

