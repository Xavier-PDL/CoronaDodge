#include "TextureManager.h"


constexpr auto moveSpeed = 150.0f;

void createEntities(sf::Sprite& player, sf::Sprite& enemy1, sf::Sprite& enemy2)
{
	auto texMan = TextureManager::Get();
	texMan.addTexture(0, "assets/player.bmp");
	texMan.addTexture(1, "assets/enemy.bmp");
	auto playerTexture = texMan.getTexture(0);
	auto enemyTexture = texMan.getTexture(1);

	player.setPosition({ 400, 300 });
	player.setColor(sf::Color::Blue);
	player.setTexture(playerTexture);
	

	enemy1.setColor(sf::Color::Red);
	enemy1.setTexture(enemyTexture);
	enemy1.setPosition({ 25.0f, 55.0f });
	enemy2.setColor(sf::Color::Red);
	enemy2.setTexture(enemyTexture);
	enemy1.setPosition({ 65.0f, 155.0f });
}

void handleInput(sf::Time dt, sf::Sprite& player)
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

void drawEntities(sf::RenderWindow& window, sf::Sprite& player, sf::Sprite& enemy1, sf::Sprite& enemy2)
{
	window.draw(player);
	window.draw(enemy1);
	window.draw(enemy2);
}


void updateEntities(sf::Sprite & player, sf::Sprite & enemy1, float dt)
{
	auto dMove = moveSpeed * dt;
	sf::Vector2f deltaPos = player.getPosition() - enemy1.getPosition();
	deltaPos /= sqrt((deltaPos.x * deltaPos.x) + (deltaPos.y * deltaPos.y));
	enemy1.move({ deltaPos.x * dMove, deltaPos.y * dMove });
}

int main()
{

	sf::Sprite player;
	sf::Sprite enemy1;
	sf::Sprite enemy2;
	sf::Texture playerTexture;
	sf::Texture enemyTexture;

	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(800, 600), "CoronaDodge!");
	createEntities(player, enemy1, enemy2);
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		handleInput(dt, player);
		window.clear(sf::Color::White);
		updateEntities(player, enemy1, dt.asSeconds());
		drawEntities(window, player, enemy1, enemy2);

		window.display();
	}

	return 0;
}