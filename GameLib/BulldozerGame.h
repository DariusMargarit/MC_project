#pragma once
#include "Board.h"
#include "BulldozerColumn.h"


class BulldozerGame
{
public:
	BulldozerGame(BoardPtr& rhs);
	BulldozerGame(BulldozerGame&& rhs) = default;
	~BulldozerGame() = default;
	BulldozerGame& operator=(const BulldozerGame& rhs) = default;
	BulldozerGame& operator=(BulldozerGame&& rhs) noexcept = default;
	
	bool CoinFlip();
	void DestroyRandomColumn();
	void MoveToRandomEmptyPlace();
	void DestroyOrMove();
	
	

private:
	void PlaceBulldozer(const Position& position);
	BoardPtr m_board;
	float m_epsilon;
	Position m_currentPosition;
	


};

