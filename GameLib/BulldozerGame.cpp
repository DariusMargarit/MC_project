#include "BulldozerGame.h"
#include <random>

BulldozerGame::BulldozerGame(BoardPtr& board)
	:m_board{ board }
{
	// Empty
}

bool BulldozerGame::CoinFlip()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	return dis(gen) < epsilon;
	
}

void BulldozerGame::PlaceBulldozer(const Position& position)
{
	m_board->PlaceColumn(position, new BulldozerColumn);
}

