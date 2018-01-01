#pragma once
#include <SFML/System/Clock.hpp>

namespace Game {
	struct Time
	{
		private:
			sf::Clock m_clock;
		
		public:

		float dt = 0.0f;
		float timeForEnemies = 0.0f;
		float timeForFps = 0.0f;
		float fullTime = 0.0f;
		float fireTime = 0.0f;
		int frames = 0;

		Time() { m_clock = sf::Clock(); }

		void Update()
		{
 			dt = m_clock.getElapsedTime().asSeconds();
			timeForEnemies += dt;
			timeForFps += dt;
			fullTime += dt;
			fireTime += dt;
			frames ++;
 			m_clock.restart();
		}
	};
}