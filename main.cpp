#include <SFML/Graphics.hpp>
#include "player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game");
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);
    //sf::Texture texture = sf::Texture();
    //texture.loadFromFile("texture.png");
    //shape.setTexture(&texture);
    //texture.create(500, 500);
    
    Player player = Player();
//Vector2f vec;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
            	if(event.key.code == sf::Keyboard::W)
            	{
            		player.m_Move(0, -1);
            	}
				if(event.key.code == sf::Keyboard::S)
            	{
            		player.m_Move(0, 1);
            	}
				if(event.key.code == sf::Keyboard::A)
            	{
            		player.m_Move(-1, 0);
            	}
				if(event.key.code == sf::Keyboard::D)
            	{
            		player.m_Move(1, 0);
            	}
            }
            
        }

        window.clear();
        window.draw(player.m_GetDrawable());
        window.display();
    }

    return 0;
}
