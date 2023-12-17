#include "Player.h"

Player::Player(const std::string_view& name, const EColor& color)
	: m_color{color}
	, m_name{name}
{
	// Empty
}

Player::Player(const Player* rhs)
	: m_color{rhs->m_color}
	, m_name{rhs->m_name}
{
	// Empty
}

Player::Player(Player&& rhs) noexcept
	: m_color{rhs.m_color}
	, m_name{rhs.m_name}
{
	rhs.m_color = EColor::NoColor;
	rhs.m_name = "";
}

Player& Player::operator=(const Player* rhs) noexcept
{
	if (this == rhs)
		return *this;

	m_name = rhs->m_name;
	m_color = rhs->m_color;

	return *this;
}

Player& Player::operator=(Player&& rhs) noexcept
{
	if (this == &rhs)
		return *this;
	m_name = rhs.m_name;
	m_color = rhs.m_color;

	rhs.m_color = EColor::NoColor;
	rhs.m_name = "";

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

void Player::SetColor(EColor rhs)
{
	m_color = rhs;
}

IPlayer* IPlayer ::Produce(std::string_view name, EColor color)
{
	return new Player{ name, color };
}
