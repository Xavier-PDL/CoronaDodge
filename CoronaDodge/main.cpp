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

int main()
{
	sf::Sprite player;
	sf::Sprite enemy1;
	sf::Sprite enemy2;
	sf::Texture playerTexture;
	sf::Texture enemyTexture;
	sf::RenderWindow window(sf::VideoMode(800, 600), "CoronaDodge!");
	
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

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::White);

		window.draw(player);
		window.draw(enemy1);
		window.draw(enemy2);

		window.display();
	}

	return 0;
}