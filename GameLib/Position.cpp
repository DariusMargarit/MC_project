#include "Position.h"

Position::Position(uint16_t x, uint16_t y)
	: m_x(x)
	, m_y(y)
{
	// Empty
}

Position::Position()
	: m_x(0)
	, m_y(0)
{
	// Empty
}

const uint16_t Position::GetX() const
{
	return m_x;
}

const uint16_t Position::GetY() const
{
	return m_y;
}

bool Position::operator==(Position position)
{
	return this->m_x == position.m_x && this->m_y == position.m_y;
}
