#pragma once
#include "World.h"
#include "Audio.h"

#include <fstream>
#include <stack>
constexpr int WndWidth	= 1200;
constexpr int WndHeight = 900;
constexpr const char* WndTitle = "CoronaDodge!";

namespace TexFile
{
	constexpr const char* PlayerWest = "assets/front.png";
	//constexpr const char* PlayerWest = "assets/player.bmp";
	//const char* PlayerEast = "assets/player.bmp";
	//const char* PlayerNorth = "assets/player.bmp";
	//const char* PlayerSouth = "assets/player.bmp";
	constexpr const char* Ammo = "assets/ammo.png";
	constexpr const char* AmmoIndicator = "assets/spraycorner.png";
	constexpr const char* Enemy = "assets/rona.png";
}

enum GameState
{
	GS_Playing,
	GS_Paused,
	GS_Menu,
	GS_GameOver
};

class Game
{
	bool isRunning = true;
	sf::Clock clock;
	sf::RenderWindow wnd;
	World world;


	int score = 0;
	int highScore;
	float scoreCount = 3.f;

	sf::Font fontScore;
	Audio deathSound;
	Audio spraySound;

	sf::Text textScore;
	sf::Font someFont;
	sf::Text textMenu;
	sf::Text textLost;
	sf::Text textLost2;

	sf::Sprite ammoIndicator;
	sf::RectangleShape ammoFill;


	std::stack<GameState> gameState;

public:
	Game();
	void load();
	void run();
private:
	void handleInput(sf::Time dt);
	void update(sf::Time dt);
	void render(sf::RenderWindow& wnd);
	void drawScore(sf::RenderWindow& wnd);
	void updateScore(sf::Time dt);
	void getHighScore();
	void writeHighScore();
	void loadFonts();
	void loadSounds();
};