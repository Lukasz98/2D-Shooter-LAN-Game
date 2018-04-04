#pragma once
#include <chrono>
#include <thread>
#include <SFML/System/Clock.hpp>
#include "log.h"

namespace Utils {

class Time
{
public:
    Time();
    void Update();

    inline float GetDt() { return dt; }
    inline float GetGameOverTime() { return gameOverTime; }
    inline void UpdateGameOverTime() { gameOverTime += dt; }
    inline void ResetGameOverTime() { gameOverTime = 0.0f; }
    inline float GetFpsTime() { return timeForFps; }
    inline float GetFps() { return fps; }

    
private:
    float dt;
    float timeForEnemies;
    float timeForFps;
    float fullTime;
    float fireTime;
    float gameOverTime;
    int frames;
    int fps = 0;
    
    sf::Clock m_clock;

    void setValues();
    
};

}
