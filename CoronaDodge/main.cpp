#include "Game.h"

int main()
{
	Audio bg(BackgroundMusic);
	bg.load("assets/bg_music.ogg");
	bg.setVolume(120.f);
	bg.setLoop(true);
	bg.play();


	Game game;
	game.load();
	game.run();
	//	auto dMove = moveSpeed * dt;
//	sf::Vector2f deltaPos = player.getPosition() - enemy1.getPosition();
//	deltaPos /= sqrt((deltaPos.x * deltaPos.x) + (deltaPos.y * deltaPos.y));
//	enemy1.move({ deltaPos.x * dMove, deltaPos.y * dMove });
	
	return 0;
}