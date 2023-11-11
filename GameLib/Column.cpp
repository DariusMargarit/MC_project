module Column;

Column::Column(IPlayer* Player)
	:m_player{Player}
{

}

Column::Column(const Column& otherColumn)
	:m_player{ otherColumn.GetPlayer() }
{

}

Column::Column(Column&& other) noexcept
	:m_player{other.m_player}
{
	other.m_player = nullptr;
}

IPlayer* Column::GetPlayer() const
{
	return m_player;
}

Column& Column::operator=(const Column& otherColumn)
{
	if (this->GetPlayer() != otherColumn.GetPlayer())
		this->m_player = otherColumn.GetPlayer();
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
