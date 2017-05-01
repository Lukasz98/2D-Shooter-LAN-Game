#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "world.h"
#include "world_loader.h"


void game(World * world);

 int SCREEN_WIDTH = 1280;
 int SCREEN_HEIGHT = 720;

int main()
{
	World * map1 = WorldLoader::LoadMap("worlds/testWorld");	

	game(map1);


	//map1();
	delete map1;
	
    return 0;
}


void game(World * world)
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");
	sf::View view(sf::FloatRect(100.0f, 100.0f, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(view);
    //window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    
	sf::Clock clock = sf::Clock();


	Player player = Player();
	//World world;
	std::vector<Bullet*> bullets;
	
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
        
        int x = 0, y = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		    x = -1; //player.m_Move(-1, 0);   
	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	        x = 1; //player.m_Move(1, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			y = -1; //player.m_Move(0, -1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			y = 1; //player.m_Move(0, 1);
		
		if (x != 0 || y != 0)
		{
			player.m_Move(x, y);   
			sf::Vector2f z = player.getPosition();
			view.setCenter(z);
			//std::cout << "\nx: " << z.x << " y: " << z.y;
			window.setView(view);		
		}
		
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && fireTime > 0.5f)
        {    
        	fireTime = 0.0f;
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
          	//std::cout << "mouse x: " << mousePos.x << ", y: " << mousePos.y << std::endl;
            //std::cout << "mouse x: " << vec.x << ", y: " << vec.y << std::endl;
            sf::Vector2f pos;
            pos.x = player.getPosition().x;
            pos.y = player.getPosition().y;
            
            // I wymiar pos.x = 640 pos.x = 360
            // II wymiar pos.x = ? ?
            
            sf::Vector2f playerDiff;
			playerDiff.x = pos.x - SCREEN_WIDTH / 2.0f;     
            playerDiff.y = pos.y - SCREEN_HEIGHT / 2.0f;     
            
            mousePos.x += playerDiff.x;
            mousePos.y += playerDiff.y;
          
            //std::cout << "ostatecznie x: " << mousePos.x << ", y: " << mousePos.y << std::endl;
            
            //if (mousePos.x > pos.x) pos.x = mousePos.x
            
            bullets.push_back(new Bullet(pos, mousePos));
        }



        window.clear();
		world->m_Draw(window);
        window.draw(player);
        for (int i = 0; i < bullets.size(); i++)
            window.draw(*bullets[i]);       
        window.display();
 		


		world->m_Update(&player, bullets, dt);
 		sf::Vector2i mouseP = sf::Mouse::getPosition(window); 
 		//std::cout << "mouse x: " << mouseP.x << ", y: " << mouseP.y << std::endl;
 		player.m_Update(dt, mouseP);
 		
		for (int i = 0; i < bullets.size(); i++)
 		{
            bool alarm = false;
        	bool bulletAlive = bullets[i]->m_Update(dt);
        	if (!bulletAlive)
        	{
        		bullets.erase(bullets.begin() + i);
        		break;
        	}
        }


#if 0
        if (timeForEnemies > 1.5f)
        {
            enemies.push_back(new Enemy()); 
            timeForEnemies = 0.0f;
        }
#endif   
        
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
}
