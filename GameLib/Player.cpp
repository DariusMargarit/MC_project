#include "Player.h"

Player::Player(const std::string_view& name, const EColor& color)
	: m_color{color}
	, m_name{name}
	, m_doubleTurn{false}
{
	// Empty
}

Player::Player(const Player*other)
	: m_color{other->m_color}
	, m_name{other->m_name}
	, m_doubleTurn{ other->m_doubleTurn }
{
	// Empty
}

Player::Player(Player&&other) noexcept
	: m_color{other.m_color}
	, m_name{other.m_name}
	, m_doubleTurn{other.m_doubleTurn}
{
	other.m_color = EColor::NoColor;
	other.m_name = "";
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

bool Player::GetDoubleTurn() const
{
	return m_doubleTurn;
}

void Player::SetColor(EColor rhs)
{
	m_color = rhs;
}

void Player::SetDoubleTurn(bool hasDoubleTurn)
{
	m_doubleTurn = hasDoubleTurn;
}

IPlayer* IPlayer ::Produce(std::string_view name, EColor color)
{
	return new Player{ name, color };
}
