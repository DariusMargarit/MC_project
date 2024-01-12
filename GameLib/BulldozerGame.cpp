#include "BulldozerGame.h"

BulldozerGame::BulldozerGame(BoardPtr& board)
	:m_board{ board }
{
	// Empty
}

void BulldozerGame::PlaceBulldozer(const Position& position)
{
	m_board->PlaceColumn(position, new BulldozerColumn);
}

