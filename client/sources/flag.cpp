#include "../headers/flag.h"


Flag::Flag(float x, float y, float w, int id)
: Tile("", x, y, w)
{
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

Flag::~Flag()
{
}
  
void Flag::SetOwner(int o)
{
    owner = o;
    if (owner == NONE)
        setTexture(&texture);
    else if (owner == NAZI)
        setTexture(&naziT);
    else
        setTexture(&polT);
}
  
void Flag::SetIsTaker(int o)
{
    isTaking = o;
    if (owner == NONE && neutral >= 100.0f)
        setTexture(&partlyTaken);
}
