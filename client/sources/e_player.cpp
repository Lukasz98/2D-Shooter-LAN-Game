#include "../headers/e_player.h"

E_Player::E_Player(int id, sf::Vector2f pos, int team)
: Body(sf::Vector2f(pos))
{
    this->id = id;
    this->team = team;

    if (team == 1)
        texture.loadFromFile("img/nazi_player.png");
    else
        texture.loadFromFile("img/pol_player.png");
    size = sf::Vector2f(70.0f, 70.0f);
    setSize(size);
    setOrigin(size.x /2, size.y /2);
    setTexture(&texture);

    if (!font.loadFromFile("img/arial.ttf"))
    {
        LOG("World:: font load failed!");
    }

    name = "Lukasz";
    text.setFont(font);
    text.setCharacterSize(25);
    text.setString(name);
    text.setColor(sf::Color::Red);
 
}

E_Player::~E_Player()
{
//  LOG("EPlayer destructor");
}

#define PREDICTION 1
#define INTERPOLATION 1

void E_Player::Update(sf::Vector2f pos, float angle)
{
#if PREDICTION && INTERPOLATION
    float a = position.x - pos.x;
    float b = position.y - pos.y;
    float diff = 20.0f; // trzba poprobowac odpowiednie wartosci

    sf::Vector2f val1 = olderRecvPos;
    sf::Vector2f val2 = pos;
    if (val1.x < val2.x) direction.x = 1.0f;
    else if (val1.x > val2.x) direction.x = -1.0f;
    else if (val1.x == val2.x) direction.x = 0.0f;

    if (val1.y < val2.y) direction.y = 1.0f;
    else if (val1.y > val2.y) direction.y = -1.0f;
    else if (val1.y == val2.y) direction.y = .0f;  
      
    if (a < diff && a > -diff && b < diff && b > -diff)
    {        
        if (olderRecvPos == pos)
        {
            position = pos;
            SetPosition(position);
            }
    }    
    else
    {
        if (team == 1) LOG("poprawiam");
        
        position = pos;
        SetPosition(position);
        text.setPosition(position.x - text.getCharacterSize() * (name.size()/4.0f), position.y + size.y / 2.0f);   
    }

    Rotate(angle);

    olderRecvPos = oldRecvPos;
    oldRecvPos = pos;
#else
    position = pos;
    SetPosition(position);
    text.setPosition(position.x - text.getCharacterSize() * (name.size()/4.0f), position.y + size.y / 2.0f);   
    Rotate(angle);
#endif
}

void E_Player::LocalUpdate(sf::Vector2i inp, float dt)
{
#if PREDICTION
    //LOG("Prediction of my player");
    float speed = 300.0f;
    float serverFactor = 1.0f;
    float ex = (inp.x * speed * dt) / serverFactor;
    float why = (inp.y * speed * dt) / serverFactor;
    position.x += ex;
    position.y += why;
    SetPosition(position);
    text.setPosition(position.x - text.getCharacterSize() * (name.size()/4.0f), position.y + size.y / 2.0f);
#endif
}


void E_Player::PredictPos(float dt)
{
#if INTERPOLATION
    //LOG("dir.x: " << direction.x << " dir.y: " << direction.y);
    float speed = 300.0f;
    float serverFactor = 1.0f;
    float ex = (direction.x * speed * dt) / serverFactor;
    float why = (direction.y * speed * dt) / serverFactor;
    position.x += ex;
    position.y += why;
    SetPosition(position);
    text.setPosition(position.x - text.getCharacterSize() * (name.size()/4.0f), position.y + size.y / 2.0f);
#endif
}
