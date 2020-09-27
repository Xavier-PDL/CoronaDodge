#include "Game.h"
#include <iostream>

Game::Game()
	:
	wnd(sf::VideoMode(WndWidth, WndHeight), WndTitle)
{
	gameState.push(GS_Menu);
}

void Game::load()
{
	
	auto texMan = TextureManager::Get();

	// entity textures
	texMan->addTexture(TexID::Enemy, TexFile::Enemy);
	texMan->addTexture(TexID::PlayerNorth, TexFile::PlayerNorth);
	texMan->addTexture(TexID::PlayerSouth, TexFile::PlayerSouth);
	texMan->addTexture(TexID::PickupAmmo, TexFile::Ammo);
	texMan->addTexture(TexID::AmmoIndicator, TexFile::AmmoIndicator);

	loadFonts();
	loadSounds();
	getHighScore();
	
	// item textures

	// sounds??
	
	auto wSize = wnd.getSize();
	ammoIndicator.setTexture(texMan->getTexture(TexID::AmmoIndicator));
	auto aiBox = ammoIndicator.getLocalBounds();
	ammoIndicator.setPosition({
		wSize.x - aiBox.width - 25.0f,
		wSize.y - aiBox.height - 50.0f });

	ammoFill.setFillColor(sf::Color::Cyan);
	ammoFill.setSize({aiBox.width, 70.0});
	//ammoFill.setPosition(ammoIndicator.getPosition());
	
	auto ammoFillPos = ammoIndicator.getPosition();
	ammoFillPos.y += (aiBox.height - ammoFill.getSize().y - 5.0f);
	ammoFill.setPosition(ammoFillPos);
	
	world.setWindow(&wnd);
	world.init();
}

void Game::loadSounds() {
	deathSound.putType(SoundEffect);
	deathSound.load("assets/cough.ogg");
	deathSound.setVolume(35.f);

	spraySound.putType(SoundEffect);
	spraySound.load("assets/spray.ogg");
	spraySound.setVolume(100.f);
}

void Game::loadFonts() {
	auto wSize = wnd.getSize();

	//Score font
	if (!fontScore.loadFromFile("assets/score_font.ttf"))
		throw "Failed to load font.";
	textScore.setFont(fontScore);
	textScore.setCharacterSize(40);
	textScore.setFillColor(sf::Color::Black);
	auto textLocalBounds = textScore.getLocalBounds();
	textScore.setOrigin({ textLocalBounds.width / 2, textLocalBounds.height / 2 });
	textScore.setPosition((float)wSize.x * .01f, (float)wSize.y * .01f);
	textScore.setFillColor(sf::Color::White);
	//Loss font
	if (!someFont.loadFromFile("assets/main_font.ttf"))
		printf("Failed to load font!!!");

	textLost.setFont(someFont);
	textLost.setString("Game Over!");
	textLost.setCharacterSize(128);
	textLocalBounds = textLost.getLocalBounds();
	textLost.setOrigin({ textLocalBounds.width / 2, textLocalBounds.height / 2 });
	textLost.setPosition({ (float)wSize.x / 2, (float)wSize.y / 4 });
	textLost.setFillColor(sf::Color::Green);
	textLost.setOutlineColor(sf::Color::Black);
	textLost.setOutlineThickness(4.0f);

	textLost2.setFont(someFont);
	textLost2.setString("Press SPACE to Restart!");
	textLost2.setCharacterSize(128);
	textLocalBounds = textLost2.getLocalBounds();
	textLost2.setOrigin({ textLocalBounds.width / 2, textLocalBounds.height / 2 });
	textLost2.setPosition({ (float)wSize.x / 2, (float)wSize.y / 2 });
	textLost2.setFillColor(sf::Color::Green);
	textLost2.setOutlineColor(sf::Color::Black);
	textLost2.setOutlineThickness(4.0f);

	textMenu.setFont(someFont);
	textMenu.setString("Press SPACE To Start Game!");
	textMenu.setCharacterSize(128);
	textLocalBounds = textMenu.getLocalBounds();
	textMenu.setOrigin({ textLocalBounds.width / 2, textLocalBounds.height / 2 });
	textMenu.setPosition({ (float)wSize.x / 2, (float)wSize.y / 4 });
	textMenu.setFillColor(sf::Color::Green);
	textMenu.setOutlineColor(sf::Color::Black);
	textMenu.setOutlineThickness(4.0f);
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
			if (gameState.top() == GS_Menu)
			{
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Space)
					{
						//world.reset();
						gameState.push(GS_Playing);
					}
				}
			}
			else if (gameState.top() == GS_GameOver)
			{
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Space)
					{
						deathSound.stop();
						world.reset();
						gameState.pop();
						score = 0;
					}
				}
			}
		}
		update(dt);
		wnd.clear(sf::Color::Black);
		render(wnd);
		wnd.display();
	}
}

void Game::handleInput(sf::Time dt)
{
	if (gameState.top() == GS_Playing)
	{
		sf::Vector2f playerVel;
		Player& player = world.getPlayer();
		auto texMan = TextureManager::Get();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			playerVel.y -= moveSpeed;
			player.setTexture(texMan->getTexture(PlayerNorth));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) 
		{
			playerVel.y += moveSpeed;
			player.setTexture(texMan->getTexture(PlayerSouth));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) playerVel.x -= moveSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) playerVel.x += moveSpeed;

		if (abs(playerVel.x) + abs(playerVel.y) > moveSpeed)
		{
			playerVel *= 0.75f;
		}
		world.updatePlayerPos(playerVel * dt.asSeconds());
	}
	//player.move(playerVel * dt.asSeconds());
}

void Game::update(sf::Time dt)
{
	handleInput(dt);
	auto player = world.getPlayer();
	if (gameState.top() == GS_Playing)
	{
		updateScore(dt);
		world.update(dt);
		auto ammoCount = player.getAmmoCount();
		sf::Vector2f fillSize = { 64.0, 70 };
		fillSize.y /= 5;
		ammoFill.setSize({ fillSize.x, fillSize.y * ammoCount });

		auto player = world.getPlayer();
		if (!player.isAlive()) {
			deathSound.play();
			gameState.push(GS_GameOver);
		}
	}
	else {
		if (score > highScore) {
			highScore = score;
			writeHighScore();
		}
		
	}

	// world.update(dt);
	//updateAudio?
	
}

void Game::render(sf::RenderWindow& wnd)
{
	auto gs = gameState.top();
	wnd.draw(ammoFill);
	wnd.draw(ammoIndicator);
	world.draw();
	if (gs == GS_Menu)
	{		
		wnd.draw(textMenu);
	}
	else if (gs == GS_Playing)
	{
		drawScore(wnd);
	}
	else if (gs == GS_GameOver)
	{
		wnd.draw(textLost);
		wnd.draw(textLost2);
		drawScore(wnd);
	}
}

void Game::drawScore(sf::RenderWindow& wnd) {
	textScore.setString("Score: " + std::to_string(score) + "\n" + "High Score: " + std::to_string(highScore));
	wnd.draw(textScore);
}

void Game::updateScore(sf::Time dt) {
	if (scoreCount <= 0) {
		score += 5;
		scoreCount = 3.f;
	}
	else
		scoreCount -= dt.asSeconds();
}

void Game::getHighScore() {
	std::ifstream infile;
	infile.open("assets/high_score.txt");
	if (!infile.is_open()) {
		throw "Could not open file";
	}
	infile >> highScore;
	infile.close();
}

void Game::writeHighScore() {
	std::ofstream outfile;
	outfile.open("assets/high_score.txt");
	if (!outfile.is_open()) {
		throw "Could not open file";
	}
	outfile << highScore;
	outfile.close();
}