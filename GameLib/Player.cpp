module Player;

Player::Player()
{}
Player::Player(char* color, const std::string& name)
	:m_color{color}
	,m_name{name}
{}
Player::Player(const Player* other)
	:m_color{other->m_color}
	,m_name{other->m_name}
{}
Player::Player(Player&& other) noexcept
	:m_color{ other.m_color }
	, m_name{ other.m_name }
{
	other.m_color = nullptr;
	other.m_name = nullptr;
}
Player::~Player()
{}

Player& Player::operator=(const Player * other)
{
	if (this == other)
		return *this;

	m_name = other->m_name;
	m_color = other->m_color;

	return *this;
}

Player& Player::operator=(Player&& other) noexcept
{
	if (this == &other)
		return *this;
	m_name = other.m_name;
	m_color = other.m_color;

	other.m_color = nullptr;
	other.m_name = nullptr;

	return *this;
}

char* Player::GetColor() const
{
	return m_color;
}

const std::string& Player::GetName() const
{
	return m_name;
}
