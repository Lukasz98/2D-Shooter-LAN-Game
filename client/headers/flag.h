#pragma once

#include <string>
#include "tile.h"
#include "log.h"

#define NONE 0
#define NAZI 1
#define POL 2

class Flag : public Tile
{
    int id, owner, isTaking;
    std::string id_c;
    float neutral, last;
    std::string texturePath_n;
    sf::Texture naziT, polT, partlyTaken;

public:
    Flag(float x, float y, float w, int id)
    : Tile("", x, y, w)
    {
        //LOG(std::string("img/flag_1_" + (char)id) + ".png");
        //std::string abc = "HEHE img/flag_1_" + std::to_string();//std::to_string(static_cast<char*>(&id));
        //abc.append((char*)&id);//std::to_string((char)id);
        //LOG(abc); 
        id_c = (char)id;
        this->id = id;
        owner = NONE;
        isTaking = NONE;
    
        naziT.loadFromFile("img/flag_1_" + id_c + ".png");
        polT.loadFromFile("img/flag_2_" + id_c + ".png");
        texture.loadFromFile("img/flag_0_" + id_c + ".png");
		partlyTaken.loadFromFile("img/flag_3_" + id_c + ".png");
        setTexture(&texture);
    }
    ~Flag() {}

    inline const int & GetId() { return id; }
    
    void SetOwner(int o)
    {
      //        LOG("SETOWNER = " << o);
        owner = o;
        if (owner == NONE) setTexture(&texture);
        else if (owner == NAZI) setTexture(&naziT);
        else setTexture(&polT);
       // texturePath = "img/flag_" + std::to_string(owner) + '_' + (char)id;
    }
    
    void SetIsTaker(int o)
	{
	  isTaking = o;
	  if (owner == NONE && neutral >= 100.0f) setTexture(&partlyTaken);
	}
	
    void SetNeutralPoints(int n) { neutral = n; }
    void SetLastPoints(int l) { last = l; }
};
