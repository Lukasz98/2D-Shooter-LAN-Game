#include "../headers/game.h"

Game::Game(Connection * connection)
: window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game"),
  view(sf::FloatRect(100.0f, 100.0f, SCREEN_WIDTH, SCREEN_HEIGHT))
{
	LOG("GAME");
	this->connection = connection;
	myId = connection->GetMyId();

	world = WorldLoader::LoadMap("../worlds/testWorld");
	world->SetPlayers(connection->GetEPlayers());
	world->SetBullets(connection->GetBullets());

	myPlayer = world->GetEPlayer(myId);

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
	LOG("PLAY");
	while (connection->isConnected() && window.isOpen())
//	while (window.isOpen())
	{
	LOG("PLAY");
		connection->Update();

		playerInput();
		connection->SendInput(inputData);
		inputData.reset();

		view.setCenter(myPlayer->GetPos());
		window.setView(view);

		window.clear();
		world->Draw(window);
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