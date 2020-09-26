#include "Game.h"

Game::Game()
	:
	wnd(sf::VideoMode(WndWidth, WndHeight), WndTitle)
{
}

void Game::load()
{
	auto texMan = TextureManager::Get();
	
	// load world texture?

	// entity textures
	texMan->addTexture(TexID::Enemy, TexFile::Enemy);
	texMan->addTexture(TexID::PlayerNorth, TexFile::PlayerWest);

	// item textures

	// sounds??

	// initialize player?
	player.setTexture(texMan->getTexture(TexID::PlayerNorth));
	player.setColor(sf::Color::Blue);
	auto pRect = player.getLocalBounds();
	player.setOrigin(pRect.width / 2, pRect.height / 2);
	auto wSize = wnd.getSize();
	player.setPosition(wSize.x / 2, wSize.y / 2);

	// initialize player spray
	playerSpray.setPointCount(3);
	playerSpray.setPoint(0, {   0, 0 });
	playerSpray.setPoint(1, { -25, -75 });
	playerSpray.setPoint(2, {  25, -75 });
	playerSpray.setPosition(player.getPosition());
	playerSpray.setFillColor(sf::Color::Cyan);

	world.init();
}

void Game::run()
{
	while (isRunning)
	{
		sf::Event event;
		sf::Time dt = clock.restart();
		while (wnd.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
				wnd.close();
			}
		}
		update(dt);
		wnd.clear(sf::Color::White);
		render(wnd);
		wnd.display();
	}
}

void Game::handleInput(sf::Time dt)
{
	sf::Vector2f playerVel;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		playerVel.y -= moveSpeed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		playerVel.y += moveSpeed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		playerVel.x -= moveSpeed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		playerVel.x += moveSpeed;
	}

	if (abs(playerVel.x) + abs(playerVel.y) > moveSpeed)
	{
		playerVel *= 0.75f;
	}

	player.move(playerVel * dt.asSeconds());
}

void Game::update(sf::Time dt)
{
	handleInput(dt);
	auto mousePosI = sf::Mouse::getPosition(wnd);
	sf::Vector2f mousePos = { (float)mousePosI.x, (float)mousePosI.y };
	sf::Vector2f wSize = { (float)wnd.getSize().x / 2, (float)wnd.getSize().y / 2 };
	auto dp = mousePos - wSize;
	//dp /= sqrt((dp.x * dp.x) + (dp.y * dp.y));
	auto sprayAngle = (atan2f(dp.y, dp.x) * 180 / 3.14) + 90.0f;
	playerSpray.setRotation(sprayAngle);
	isSpraying = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	world.updateEntities();
	// world.update(dt);
	//updateAudio?
}

void Game::render(sf::RenderWindow& wnd)
{
	world.draw(wnd);
	wnd.draw(player);
	if(isSpraying)
		wnd.draw(playerSpray);
}
