#define SFML_STATIC
#include <SFML/Graphics.hpp>
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "opengl32.lib")
#ifdef _DEBUG
#pragma comment(lib, "sfml-system-s-d.lib")
#pragma comment(lib, "sfml-window-s-d.lib")
#pragma comment(lib, "sfml-graphics-s-d.lib")
#else
#pragma comment(lib, "sfml-system-s.lib")
#pragma comment(lib, "sfml-window-s.lib")
#pragma comment(lib, "sfml-graphics-s.lib")
#endif

sf::Sprite player;
sf::Sprite enemy1;
sf::Sprite enemy2;
sf::Texture playerTexture;
sf::Texture enemyTexture;

constexpr auto moveSpeed = 150.0f;

void createEntities()
{
	playerTexture.loadFromFile("assets/player.bmp");
	enemyTexture.loadFromFile("assets/enemy.bmp");

	player.setColor(sf::Color::Blue);
	player.setTexture(playerTexture);
	enemy1.setColor(sf::Color::Red);
	enemy1.setTexture(enemyTexture);
	enemy1.setPosition({ 25.0f, 55.0f });
	enemy2.setColor(sf::Color::Red);
	enemy2.setTexture(enemyTexture);
	enemy1.setPosition({ 65.0f, 155.0f });
}

void drawEntities(sf::RenderWindow& window)
{
	window.draw(player);
	window.draw(enemy1);
	window.draw(enemy2);
}

void handleInput(sf::Time dt)
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

void updateEntities(sf::Time dt)
{
	// Todo
}

int main()
{
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(800, 600), "CoronaDodge!");
	createEntities();
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		handleInput(dt);
		window.clear(sf::Color::White);

		drawEntities(window);

		window.display();
	}

	return 0;
}