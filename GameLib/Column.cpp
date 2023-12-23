#include "Column.h"

Column::Column(IPlayer* player)
	:m_player{ player }
{
	// Empty
}

Column::Column(const Column& rhs)
	:m_player{ rhs.m_player }
{
	// Empty
}

Column::Column(Column&& rhs) noexcept
	:m_player{ rhs.m_player }
{
	rhs.m_player = nullptr;
}

IPlayer* Column::GetPlayer() const noexcept
{
	return m_player;
}

Column& Column::operator=(const Column& rhs) noexcept
{
	if (m_player != rhs.m_player)
		m_player = rhs.m_player;
	return *this;
}

Column& Column::operator=(Column&& rhs) noexcept
{
	if (this == &rhs)
		return *this;
	m_player = rhs.m_player;

	rhs.m_player = nullptr;

	return *this;
}