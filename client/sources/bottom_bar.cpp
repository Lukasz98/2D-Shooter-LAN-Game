#include "../headers/bottom_bar.h"


BottomBar::BottomBar(sf::Vector2f s, std::vector<const sf::Texture *> f)
: color(25.0f, 25.0f, 25.0f) 
{
  setSize(s);
  setFillColor(color);

  for (size_t i = 0; i < f.size(); i++)
  {
	flags.push_back(sf::RectangleShape(sf::Vector2f(64.0f, 64.0f)));
  }

  SetFlagsT(f);

  font.loadFromFile("img/arial.ttf");
  naziText.setFont(font);
  naziText.setCharacterSize(30);
  naziText.setColor(sf::Color::Red);
  //  naziText.setString(std::to_string(naziTickets));
  polText.setFont(font);
  polText.setCharacterSize(30.0f);
  polText.setColor(sf::Color::Red);
}

BottomBar::~BottomBar()
{
}

void BottomBar::DrawContent(sf::RenderWindow * window)
{
  for (auto & f : flags)
	window->draw(f);

  window->draw(naziText);
  window->draw(polText);
}

void BottomBar::SetPosition(float x, float y)
{
  setPosition(x, y);
  for (size_t i = 0; i < flags.size(); i++)
  {
	flags[i].setPosition(x + 64.0f * i, y);
  }

  naziText.setPosition(getPosition().x + (flags.size()+2) * 64.0f, getPosition().y);
  polText.setPosition(getPosition().x + (flags.size()+2) * 64.0f, getPosition().y + 30.0f);
 
}


