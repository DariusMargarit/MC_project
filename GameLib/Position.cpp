#include "Position.h"


Position::Position(const uint16_t& row, const uint16_t& column)
	: m_row{row}
	, m_column{column}
{
	// Empty
}


Position::Position()
	: Position{ EmptyPosition() }
{
	// Empty
}

const uint16_t Position::GetRow() const noexcept
{
	return m_row;
}

const uint16_t Position::GetColumn() const noexcept
{
	return m_column;
}

bool Position::IsEqual(const uint16_t& row, const uint16_t& column)
{
	return row == m_row && column == m_column;
}

bool Position::operator==(const Position& position)
{
	return IsEqual(position.m_row,position.m_column);
}

bool Position::operator!=(const Position& position)
{
	return !IsEqual(position.m_row, position.m_column);
}

const Position& Position::EmptyPosition()
{
	static const Position& position{UINT16_MAX, UINT16_MAX};
	return position;
}