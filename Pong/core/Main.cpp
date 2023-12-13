#include "Game.h"



int main()
{
	auto game = sbt::Game::getInstance();
	game->createGame();

	return 0;
}