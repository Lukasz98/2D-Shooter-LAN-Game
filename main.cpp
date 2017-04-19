#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include "player.h"
#include "bullet.h"
#include "enemy.h"

 int SCREEN_WIDTH = 800;
 int SCREEN_HEIGHT = 600;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");
    //window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    
	sf::Clock clock = sf::Clock();

    Player player = Player();
    std::vector<Bullet*> bullets;
    std::vector<Enemy*> enemies;	
    float dt = 0.0f, timeForEnemies = 0.0f, timeForFps = 0.0f, fullTime = 0.0f;
	float fireTime = 0.0f;
	int frames = 0;
	

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();            
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		    player.m_Move(-1, 0);   
	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	        player.m_Move(1, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			player.m_Move(0, -1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			player.m_Move(0, 1);   

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && fireTime > 0.5f)
        {    
        	fireTime = 0.0f;
            sf::Vector2i vec = sf::Mouse::getPosition(window);
            sf::Vector2f pos;
            pos.x = player.getPosition().x;// + player.getSize().x /2;
            pos.y = player.getPosition().y;// + player.getSize().y /2;
            bullets.push_back(new Bullet(pos, vec));
        }



        window.clear();
        window.draw(player);
        for (int i = 0; i < bullets.size(); i++)
            window.draw(*bullets[i]);
		for (int i = 0; i < enemies.size(); i++)                
            window.draw(*enemies[i]);        
        window.display();
 		



 		player.m_Update(dt, sf::Mouse::getPosition(window));
 		
		for (int i = 0; i < bullets.size(); i++)
 		{
            bool alarm = false;
        	bullets[i]->m_Update(dt);
    		for (int j = 0; j < enemies.size(); j++)        
            {
                if (bullets[i]->m_Overlaps(*enemies[j]))
                {
                    enemies[j]->m_GetDamage(51.0f);
                    bullets.erase(bullets.begin() + i);
                    alarm = true;                    
                    break;                
                }
            }                    
            if (alarm) break;
        }
     	
        for (int i = 0; i < bullets.size(); i++)
 		{
            sf::Vector2f pos = bullets[i]->getPosition();
            if(pos.x > SCREEN_WIDTH || pos.x < 0.0f || pos.y < 0.0f || pos.y > SCREEN_HEIGHT)
            {
                bullets.erase(bullets.begin() + i);
                break;
            }
        }

		for (int i = 0; i < enemies.size(); i++)        
        {
            if (enemies[i]->m_Update(dt, player.getPosition()))
            {
                enemies.erase(enemies.begin() + i);
                break;
            }
        }

        if (timeForEnemies > 8.5f)
        {
            enemies.push_back(new Enemy()); 
            timeForEnemies = 0.0f;
        }
        
        
 		if (timeForFps > 1.0f)
 		{
 			//std::cout << "!!!!!!!!!!!!!!!!!!!!!! FPS: " << frames << std::endl;
 			timeForFps = 0.0f;
 			frames = 0;
 		}
 		
 		dt = clock.getElapsedTime().asSeconds();
        timeForEnemies += dt;
        timeForFps += dt;
        fullTime += dt;
        fireTime += dt;
        frames ++;
 		clock.restart();
    }

    return 0;
}

