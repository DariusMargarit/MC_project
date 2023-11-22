#include <memory>

#include "Twixt.h"
#include "Player.h"
#include "Game.h"

void Twixt::Run() {
	IPlayer* firstPlayer = new Player("Player1", EColor::Blue);
	IPlayer* secondPlayer = new Player("Player2", EColor::Red);
	uint16_t boardSize = 24;
	IGame* game = new Game(firstPlayer, secondPlayer, boardSize);

	bool isGameActive = true;
	while (isGameActive) {
		IPlayer* currentPlayer = game->GetTurn();
	}
	
}