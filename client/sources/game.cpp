#include "../headers/game.h"

Game::Game(Connection * connection)
: window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game"),
  view(sf::FloatRect(100.0f, 100.0f, SCREEN_WIDTH, SCREEN_HEIGHT))
{
    LOG("GAME");
    this->connection = connection;
    myId = connection->GetMyId();

    world = WorldLoader::LoadMap("../worlds/" + connection->GetMapName());
    world->SetPlayers(connection->GetEPlayers());
    world->SetBullets(connection->GetBullets());

    world->SetMyPlayerId(myId);
    myPlayer = world->GetMyPlayer();

    window.setView(view);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    play();
}

Game::~Game()
{
    delete world;
}

void Game::play()
{
    BottomBar guiBar{sf::Vector2f(1280.0f, 64.0f), world->GetFlagsT()};

    sf::Font font;
    font.loadFromFile("img/arial.ttf");
    sf::Text won_txt;
    won_txt.setFont(font);
    won_txt.setCharacterSize(90);
    won_txt.setColor(sf::Color::Blue);
    
    while (connection->isConnected() && window.isOpen())
    {
        connection->Update(world);

        playerInput();
        connection->SendInput(inputData);
        inputData.reset();

        sf::Vector2f vec;
        vec.x = myPlayer->GetPos().x;
        vec.y = myPlayer->GetPos().y + 32.0f;
        view.setCenter(vec);
        window.setView(view);

        int naziT = connection->GetNaziTickets();
        int polT = connection->GetPolTickets();
        guiBar.SetFlagsT(world->GetFlagsT());
        guiBar.SetNaziTickets(naziT);
        guiBar.SetPolTickets(polT);

        if (naziT <= 0)
        {
            won = POL;
            won_txt.setString("Poland won!");
            won_txt.setPosition(vec.x - 1280.0f * 0.4f, vec.y);
        }
        else if (polT <= 0)
        {
            won = NAZI;
            won_txt.setString("German nazists won!");
            won_txt.setPosition(vec.x - 1280.0f * 0.4f, vec.y);
        }
        else
            won = 0;
        
        window.clear();
        world->Draw(window);
        guiBar.SetPosition(vec.x - 1280.0f / 2.0f, vec.y + 297.0f);
        window.draw(guiBar);
        guiBar.DrawContent(&window);
        if (won != 0)
            window.draw(won_txt);
        window.display();

        time.Update();
    }
}

void Game::playerInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    
    inputData.updateMousePos(sf::Mouse::getPosition(window));

    if (won == 0)
    {
        
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        inputData.x = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        inputData.x = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        inputData.y = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        inputData.y = 1;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && time.fireTime > 0.5f)
    {
        time.fireTime = 0.0f;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        Bullet * b = new Bullet(myPlayer->getPosition(), mousePos, myId, bulletIds);
        world->AddBullet(b);
        inputData.speedRatio = b->GetSpeedRatio();
        inputData.mouseClick = true;
        inputData.bulletId = bulletIds;
        bulletIds ++;
    }
    
    }
}
