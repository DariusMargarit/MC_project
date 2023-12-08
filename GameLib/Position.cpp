#include "Position.h"


Position::Position(const uint16_t& row, const uint16_t& column)
	: m_row{row}
	, m_column{column}
{
	// Empty
}

Position::Position(const Position& otherPosition)
	: m_row{otherPosition.m_row}
	, m_column{otherPosition.m_column}
{
	// Empty
}

Position::Position(Position&& otherPosition) noexcept
	: m_row(std::move(otherPosition.m_row)), m_column(std::move(otherPosition.m_column))
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

bool Position::IsEqual(const uint16_t& row, const uint16_t& column) const
{
	return row == m_row && column == m_column;
}

bool Position::operator==(const Position& position) const
{
	return IsEqual(position.m_row,position.m_column);
}

bool Position::operator!=(const Position& position) const
{
	return !IsEqual(position.m_row, position.m_column);
}

Position& Position::operator=(const Position& position)
{
	if (this != &position)
	{
		m_row = position.m_row;
		m_column = position.m_column;
	}
	return *this;
}

Position& Position::operator=(Position&& position) noexcept {
	if (this != &position) {
		m_row = std::move(position.m_row);
		m_column = std::move(position.m_column);
	}
	return *this;
}

const Position& Position::EmptyPosition()
{
	static const Position& position{UINT16_MAX, UINT16_MAX};
	return position;
}