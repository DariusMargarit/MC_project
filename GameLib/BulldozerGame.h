#pragma once
#include "Board.h"
#include "BulldozerColumn.h"


class BulldozerGame
{
public:
	BulldozerGame(BoardPtr& rhs);
	
	bool CoinFlip();
	void DestroyRandomColumn(PlayerPtr firstPlayer, PlayerPtr secondPlayer);
	void MoveToRandomEmptyPlace();
	void DestroyOrMove(PlayerPtr firstPlayer, PlayerPtr secondPlayer);
	
	

private:
	void PlaceBulldozer(const Position& position);
	BoardPtr m_board;
	float m_epsilon;
	Position m_currentPosition;
	


};

