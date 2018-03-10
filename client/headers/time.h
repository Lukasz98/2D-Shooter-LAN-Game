#pragma once
#include <SFML/System/Clock.hpp>
#include "log.h"

namespace Utils {

struct Time
{
    Time() { m_clock = sf::Clock(); }

    void Update()
    {
        dt = m_clock.getElapsedTime().asSeconds();
        m_clock.restart();
        setValues();
    }

    float dt = 0.0f;
    float timeForEnemies = 0.0f;
    float timeForFps = 0.0f;
    float fullTime = 0.0f;
    float fireTime = 0.0f;
    int frames = 0;

private:
    sf::Clock m_clock;

    void setValues() 
    {
        fullTime += dt;
        fireTime += dt;
        frames ++;
    }
    
};

}
