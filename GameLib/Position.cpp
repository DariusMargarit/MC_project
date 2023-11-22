#include "Position.h"


Position::Position(uint16_t row, uint16_t column)
	: m_row(row)
	, m_column(column)
{
	// Empty
}


Position::Position()
	: Position(EmptyPosition())
{
	// Empty
}

const uint16_t Position::GetRow() const
{
	return m_row;
}

const uint16_t Position::GetColumn() const
{
	return m_column;
}

bool Position::IsEqual(uint16_t row, uint16_t column)
{
	return row == m_row && column == m_column;
}

bool Position::operator==(Position position)
{
	return this->m_row == position.m_row && this->m_column == position.m_column;
}

const Position& Position::EmptyPosition()
{
	static const Position& position{UINT16_MAX, UINT16_MAX};
	return position;
}