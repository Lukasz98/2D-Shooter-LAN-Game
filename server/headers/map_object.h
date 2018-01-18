#pragma once
#include <memory>
//#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
//#include <SFML/Graphics/Texture.hpp>
#include "body.h"
#include "log.h"


class MapObject// : public sf::RectangleShape
{
public:
	MapObject();
	~MapObject();

	void m_SetPosition(sf::Vector2f _pos) { m_pos = _pos; }
	void m_SetSize(sf::Vector2f _size) { m_size = _size; }

	bool m_Overlaps(const std::shared_ptr<Body> _body);

	const sf::Vector2f & GetPosition() { return m_pos; }
	const sf::Vector2f & GetSize() { return m_size; }

protected:
	sf::Vector2f m_pos, m_size;
};

