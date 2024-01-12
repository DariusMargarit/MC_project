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

void BulldozerGame::DestroyRandomColumn()
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<uint16_t> distribution(0, m_board->GetSize() - 1);

	uint16_t randomRowIndex{ distribution(gen) };
	uint16_t randomColumnIndex{ distribution(gen) };
	Position position{ randomRowIndex ,randomRowIndex };

	while (m_board->GetElement(position) == nullptr)
	{
		randomRowIndex = distribution(gen);
		randomColumnIndex = distribution(gen);
		position = { randomRowIndex ,randomColumnIndex };
	}

	m_board->RemoveColumn(position);
	PlaceBulldozer(position);

}

void BulldozerGame::PlaceBulldozer(const Position& position)
{
	m_board->PlaceColumn(position, new BulldozerColumn);
}

