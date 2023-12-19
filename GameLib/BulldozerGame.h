#pragma once
#include "IGame.h"
#include "Board.h"
#include "Player.h"


class BulldozerGame : public IGame
{
public:
	BulldozerGame(const BulldozerGame& rhs);
	BulldozerGame(BulldozerGame&& rhs) = default;
	~BulldozerGame();
	
private:
	Board* m_board;
	uint16_t m_boardSize;
	IPlayer* m_player1, * m_player2, * m_turn, *m_bulldozer;
	ObserverList m_observers;


};

