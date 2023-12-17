#include "Player.h"

Player::Player(const std::string_view& name, const EColor& color)
	: m_color{color}
	, m_name{name}
{
	// Empty
}

Player::Player(const Player* other)
	: m_color{other->m_color}
	, m_name{other->m_name}
{
	// Empty
}

Player::Player(Player&& other) noexcept
	: m_color{other.m_color}
	, m_name{other.m_name}
{
	other.m_color = EColor::NoColor;
	other.m_name = "";
}

Player& Player::operator=(const Player* other) noexcept
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

	other.m_color = EColor::NoColor;
	other.m_name = "";

	return *this;
}

EColor Player::GetColor() const noexcept
{
	return m_color;
}

std::string_view Player::GetName() const noexcept
{
	return m_name;
}

void Player::SetColor(EColor otherColor)
{
	m_color = otherColor;
}

IPlayer* IPlayer ::Produce(std::string_view name, EColor color)
{
	return new Player{ name, color };
}
