#pragma once
#include <memory>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "e_player.h"
#include "bullet.h"
#include "wall.h"
#include "floor.h"
#include "tile.h"
#include "flag.h"
#include "log.h"



class World
{
public:
	World();
	~World();

	void Draw(sf::RenderWindow & window);

    void SetMap(std::string map, int mapW, int mapH)
    {
        this->map = map;
        this->mapW = mapW;
        this->mapH = mapH;
        
        float tileW = 64.0f;

        for (int y = 0; y < mapH; y++)
        {
            for (int x = 0; x < mapW; x++)
            {
                std::string texture;
                int index = x + y + (mapW - 1) * y;
//                int index = map.size() - 1 - (x + y + (mapW-1)*y);
//LOG(map.size() << ", " << x + y << ", " << mapW*y << ", index="<<index);
                switch (map[index])
                {
                    case 'w': { texture = "img/wall.png"; break; }
                    case 'g': { texture = "img/grass.png"; break; }
				    case 'z': { texture = "img/thing.png"; break; }
                    //case 'A': { texture = "img/flag_a_un.png"; break; }
                }
//LOG("X="<<tileW*x<<" Y="<<tileW*(mapH-y));
//                tiles.push_back(new Tile(texture, 0.0f + (tileW * x), 0.0f + (tileW * y), tileW));
                if (map[index] == 'A' || map[index] == 'B' || map[index] == 'C')
                    flags.push_back(new Flag(tileW * x, y * tileW, tileW, map[index]));
                else
                    tiles.push_back(new Tile(texture, 0.0f + (tileW * x), (y) * tileW, tileW));
            }
        }
	    
    }

	void SetPlayers(std::vector<std::shared_ptr<E_Player>> * ePlayers) { this->ePlayers = ePlayers; }
	void SetBullets(std::vector<Bullet*> * bullets) { this->bullets = bullets; }
	void AddBullet(Bullet * bullet) { bullets->push_back(bullet); }
    
    void UpdateFlag(int id, int owner, int isTaker, float neutralPoints, float lastPoints)
    {
        for (auto f : flags)
        {
            if (f->GetId() == id)
            {
                f->SetOwner(owner);
                f->SetIsTaker(isTaker);
                f->SetNeutralPoints(neutralPoints);
                f->SetLastPoints(lastPoints);
                break;
            }
        }
    }

	std::vector<const sf::Texture *> GetFlagsT()
	{
	  std::vector<const sf::Texture *> t;
	  for (auto f : flags)
		t.push_back(f->getTexture());

	  return t;
	}
		
	
    const std::shared_ptr<E_Player> GetEPlayer(int id);


private:
	std::vector<Bullet*> * bullets;
	std::vector<std::shared_ptr<E_Player>> * ePlayers;

    std::string map;
    int mapW, mapH;
    std::vector<Tile*> tiles;
    std::vector<Flag*> flags;

	sf::Font font;
	sf::Text text;
};
