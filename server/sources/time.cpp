#include "../headers/time.h"

namespace Game {

Time::Time() 
{
	m_clock = sf::Clock();
	dt = 0.0f;
	timeForEnemies = 0.0f;
	timeForFps = 0.0f;
	fullTime = 0.0f;
	fireTime = 0.0f;
	frames = 0;
} 
		
void Time::Update()
{
	dt = m_clock.getElapsedTime().asSeconds();
	
	float frameGoal = 60.0f;

	if (dt < 1.0f / frameGoal)
	{
		float timeForSleep = (1.0f / frameGoal - dt) * 1000.0f; 
		std::this_thread::sleep_for(std::chrono::milliseconds((int)timeForSleep));
		dt = m_clock.getElapsedTime().asSeconds();
	}

	
	m_clock.restart();
	setValues();
	//LOG(dt);
}

void Time::setValues()
{
	timeForEnemies += dt;
	timeForFps += dt;
	fullTime += dt;
	fireTime += dt;
	frames ++;

	if (timeForFps > 1.0f)
	{
		//LOG(frames);
		timeForFps = 0.0f;
		frames = 0;
	}
}

}