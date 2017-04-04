#include "bullet.h"

Bullet::Bullet()
{
    m_texture.loadFromFile("img/texture.png");
    //setPosition(20.0f, 20.0f);
    setRadius(30.0f);
    setTexture(&m_texture);
}

Bullet::Bullet(sf::Vector2f _pos, sf::Vector2i _direction)
{
    m_texture.loadFromFile("img/texture.png");
    //setPosition(20.0f, 20.0f);
    m_position = _pos;
    m_direction = sf::Vector2f((float) _direction.x, (float) _direction.y);
    m_speedRatio = Math_calc::Get_xy_SpeedRatio(m_position, m_direction);
    m_speed = 1000.0f;
    
    setRadius(15.0f);
    setPosition(m_position);
    setTexture(&m_texture);
}

Bullet::~Bullet()
{

}


void Bullet::m_Update(float _dt)
{
	m_dt = _dt;
	
	m_position.x += m_speed * m_speedRatio.x * _dt;
	m_position.y += m_speed * m_speedRatio.y * _dt;
	//std::cout<<m_position.x<<", "<<m_position.y<<std::endl;
	setPosition(m_position);
}

bool Bullet::m_Overlaps(sf::RectangleShape _rectShape)
{
    sf::Vector2f rectPos = _rectShape.getPosition();
    sf::Vector2f rectSize = _rectShape.getSize();
    float myWidth = getRadius() *2;  
    
    if (m_position.x + myWidth > rectPos.x && m_position.x < rectPos.x + rectSize.x
        && m_position.y < rectPos.y + rectSize.y)
        return true;

    if (m_position.x > rectPos.x + rectSize.x) return false;
    if (m_position.x + myWidth < rectPos.x) return false;
    if (m_position.y > rectPos.y + rectSize.y) return false;
    if (m_position.y + myWidth < rectPos.y) return false;
    
    return true; 
}


