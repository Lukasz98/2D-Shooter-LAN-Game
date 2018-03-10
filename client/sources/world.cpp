#include "../headers/world.h"

World::World()
{
    if (!font.loadFromFile("img/arial.ttf"))
    {
        LOG("World:: font load failed!");
    }

    text.setFont(font);
    text.setCharacterSize(50);
    text.setString("Lukasz lubi placki");
    text.setColor(sf::Color::Red);
}

World::~World() 
{
}



void World::Draw(sf::RenderWindow & window)
{   
    for (auto tile : tiles)
    {
        window.draw(*tile);
    }

    for (auto flag : flags)
        window.draw(*flag);

    for (auto const ePlayer : (*ePlayers))
    {
        window.draw(*ePlayer);
        window.draw(ePlayer->GetText());
    }
    
    for (auto bullet : *bullets)
        window.draw(*bullet);

    window.draw(text);
}

const std::shared_ptr<E_Player> World::GetEPlayer(int id)
{
    for (auto player : *ePlayers)
    {
        if (player->GetId() == id)
        {
            return player;
        }
    }
}

void World::SetMap(std::string map, int mapW, int mapH)
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
            switch (map[index])
            {
                case 'w': { texture = "img/wall.png"; break; }
                case 'g': { texture = "img/grass.png"; break; }
                case 'z': { texture = "img/thing.png"; break; }
            }

            if (map[index] == 'A' || map[index] == 'B' || map[index] == 'C')
                flags.push_back(new Flag(tileW * x, y * tileW, tileW, map[index]));
            else
                tiles.push_back(new Tile(texture, 0.0f + (tileW * x), (y) * tileW, tileW));
        }
    }
        
}
    
void World::UpdateFlag(int id, int owner, int isTaker, float neutralPoints, float lastPoints)
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

std::vector<const sf::Texture *> World::GetFlagsT()
{
    std::vector<const sf::Texture *> t;
    for (auto f : flags)
        t.push_back(f->getTexture());

    return t;
}



