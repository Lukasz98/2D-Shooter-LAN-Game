#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "body.h"


class MapObject : public sf::RectangleShape
{
public:
	MapObject();
	~MapObject();

	void m_SetPosition(sf::Vector2f _pos);
	void m_SetSize(sf::Vector2f _size);
	void m_SetTexture(std::string _path);

	bool m_Overlaps(const Body * _body);

protected:
	sf::Vector2f m_pos, m_size;
	sf::Texture m_texture;
};

