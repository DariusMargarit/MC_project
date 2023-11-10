module Player;

char* Player::GetColor() const
{
	return m_color;
}

const std::string& Player::GetName() const
{
	return m_name;
}
