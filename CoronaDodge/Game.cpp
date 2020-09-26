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
	
	if (!someFont.loadFromFile("assets/main_font.ttf"))
		printf("Failed to load font!!!");
	textLost.setFont(someFont);
	textLost.setString("Game Over!");
	textLost.setCharacterSize(128);
	auto textLocalBounds = textLost.getLocalBounds();
	textLost.setOrigin({ textLocalBounds.width / 2, textLocalBounds.height / 2 });
	auto wSize = wnd.getSize();
	textLost.setPosition({ (float)wSize.x / 2, (float)wSize.y / 4 });
	textLost.setFillColor(sf::Color::Green);
	// item textures

	// sounds??

	world.setWindow(&wnd);
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
	world.updatePlayerPos(playerVel * dt.asSeconds());
	//player.move(playerVel * dt.asSeconds());
}

void Game::update(sf::Time dt)
{
	handleInput(dt);
	auto player = world.getPlayer();
	if (player.isAlive())
	{
		world.update(dt);
	}
	// world.update(dt);
	//updateAudio?
}

void Game::render(sf::RenderWindow& wnd)
{
	// ui
	world.draw();
	auto player = world.getPlayer();
	if (!player.isAlive())
		wnd.draw(textLost);
}
