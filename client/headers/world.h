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

    void Draw(sf::RenderWindow & window, const E_Player * myPlayer);

    void SetMap(std::string map, int mapW, int mapH);
    //void SetPlayers(std::vector<std::shared_ptr<E_Player>> * ePlayers) { this->ePlayers = ePlayers; }
    //void SetBullets(std::vector<Bullet*> * bullets) { this->bullets = bullets; }
    //void AddBullet(Bullet * bullet) { bullets->push_back(bullet); }
    void UpdateFlag(int id, int owner, int isTaker, float neutralPoints, float lastPoints);

    //void SetMyPlayerId(int id);
    
    std::vector<const sf::Texture *> GetFlagsT();        
    //const std::shared_ptr<E_Player> GetMyPlayer();


private:
    //std::vector<Bullet*> * bullets;
    //std::vector<std::shared_ptr<E_Player>> * ePlayers;

    std::string map;
    int mapW, mapH;
    std::vector<Tile*> tiles; //pewnie musze je usunac
    std::vector<Flag*> flags;

    //std::shared_ptr<E_Player> clientPlayer;
    
    sf::Font font;
    sf::Text text;
};
