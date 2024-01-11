#include "MinedGame.h"

MinedGame::MinedGame(BoardPtr board)
	:m_board{board}
{
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

void MinedGame::DestroyArea(const Position& position)
{
	uint16_t rowPosition= position.GetRow(), columnPosition = position.GetColumn();
	
	for (uint16_t row{rowPosition - 1}; row != rowPosition + 1; ++row)
	{
		for (uint16_t column{columnPosition - 1}; column != columnPosition + 1; ++column)
		{
			if((row != 0 && column !=0) &&
			   (row != 0 && column != m_board->GetSize() - 1) &&
			   (row != m_board->GetSize() - 1 && column != 0) &&
			   (row != m_board->GetSize() - 1 && column != m_board->GetSize() - 1))
					m_board->RemoveColumn({ row,column });
		}
	}
}

void MinedGame::PlaceMine(const Position& position)
{
	m_board->PlaceColumn(position, new MinedColumn);
}