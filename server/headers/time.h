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

private:
	float dt;
	float timeForEnemies;
	float timeForFps;
	float fullTime;
	float fireTime;
	int frames;

	sf::Clock m_clock;

	void setValues();
	
};

}