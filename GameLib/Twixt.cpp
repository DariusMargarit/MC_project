#include "Twixt.h"

void Twixt::Run() {
	IPlayer* firstPlayer = new Player("Player1", "RED");
	IPlayer* secondPlayer = new Player("Player2", "BLACK");
	uint16_t boardSize = 24;
	IGame* game = new Game(firstPlayer, secondPlayer, boardSize);

	bool isGameActive = true;
	while (isGameActive) {
		IPlayer* currentPlayer = game->GetTurn();
	}
	
}