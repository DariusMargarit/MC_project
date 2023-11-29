#include "Column.h"

Column::Column(IPlayer* player)
	:m_player{ player }
{
	// Empty
}

Column::Column(const Column& other)
	:m_player{ other.m_player }
{
	// Empty
}

Column::Column(Column&& other) noexcept
	:m_player{ other.m_player }
{
	other.m_player = nullptr;
}

IPlayer* Column::GetPlayer() const noexcept
{
	return m_player;
}

Column& Column::operator=(const Column& other) noexcept
{
	if (m_player != other.m_player)
		m_player = other.m_player;
	return *this;
}

Column& Column::operator=(Column&& other) noexcept
{
	if (this == &other)
		return *this;
	m_player = other.m_player;

	other.m_player = nullptr;

	return *this;
}
