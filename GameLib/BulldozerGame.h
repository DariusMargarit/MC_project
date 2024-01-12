#pragma once
#include "Board.h"
#include "BulldozerColumn.h"


class BulldozerGame : public std::monostate
{
public:
	BulldozerGame(BoardPtr& rhs);
	BulldozerGame(BulldozerGame&& rhs) = default;
	~BulldozerGame() = default;
	BulldozerGame& operator=(const BulldozerGame& rhs) = default;
	BulldozerGame& operator=(BulldozerGame&& rhs) noexcept = default;
	
	bool CoinFlip();

private:
	void PlaceBulldozer(const Position& position);
	BoardPtr m_board;
	float epsilon = 0.99;
	


};

