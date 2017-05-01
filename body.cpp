#include "body.h"

Body::Body()
{

}

Body::~Body()
{

}
	
void Body::m_ReactOnCollision()
{
std::cout << "\nKolizja";
	m_position.x += (m_speedRatio.x * -1) * m_speed * m_dt;
	m_position.y += (m_speedRatio.y * -1) * m_speed * m_dt;
	setPosition(m_position);
}

