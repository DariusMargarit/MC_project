#include "MinedGame.h"

MinedGame::MinedGame(BoardPtr board)
	:m_board{board}
{
	// Empty
}


void MinedGame::AddMines()
{
	uint16_t numberMines{ (uint16_t)((5.0 / 100.0) * (m_board->GetSize() * m_board->GetSize())) };
	while (numberMines)
	{
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> distr(1, m_board->GetSize() - 2);

		uint16_t row{ (uint16_t)distr(eng) }, column{ (uint16_t)distr(eng) };
		Position pos{ row,column };

		PlaceMine(pos);
		--numberMines;
	}
}

void MinedGame::PlaceMine(const Position& position)
{
	m_board->PlaceColumn(position, new MinedColumn);
}