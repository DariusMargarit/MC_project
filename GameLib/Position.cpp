#include "Position.h"

Position::Position(uint16_t row, uint16_t column)
	: m_row(row)
	, m_column(column)
{
	// Empty
}

Position::Position()
	: m_row(UINT16_MAX)
	, m_column(UINT16_MAX)
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

bool Position::operator==(Position position)
{
	return this->m_row == position.m_row && this->m_column == position.m_column;
}
