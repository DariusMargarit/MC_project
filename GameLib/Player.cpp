#include "Player.h"

Player::Player(const std::string_view& name, const EColor& color,
			   const uint16_t& BridgeCounter,const uint16_t& ColumnCounter)
	: m_color{color}
	, m_name{name}
	, m_doubleTurn{false}
	, m_BridgeCounter{BridgeCounter}
	, m_ColumnCounter{ColumnCounter}
{
	// Empty
}

Player::Player(const Player*other)
	: m_color{other->m_color}
	, m_name{other->m_name}
	, m_doubleTurn{other->m_doubleTurn}
	, m_BridgeCounter{other->m_BridgeCounter}
	, m_ColumnCounter{other->m_ColumnCounter}
{
	// Empty
}

Player::Player(Player&&other) noexcept
	: m_color{other.m_color}
	, m_name{other.m_name}
	, m_doubleTurn{other.m_doubleTurn}
	, m_BridgeCounter{other.m_BridgeCounter}
	, m_ColumnCounter{other.m_ColumnCounter}
{
	other.m_color = EColor::NoColor;
	other.m_name = "";
	other.m_BridgeCounter = NULL;
	other.m_ColumnCounter = NULL;
}

Player& Player::operator=(const Player* rhs) noexcept
{
	if (this == rhs)
		return *this;

	m_name = rhs->m_name;
	m_color = rhs->m_color;
	m_BridgeCounter = rhs->m_BridgeCounter;
	m_ColumnCounter = rhs->m_ColumnCounter;

	return *this;
}

Player& Player::operator=(Player&& rhs) noexcept
{
	if (this == &rhs)
		return *this;
	m_name = rhs.m_name;
	m_color = rhs.m_color;
	m_BridgeCounter = rhs.m_BridgeCounter;
	m_ColumnCounter = rhs.m_ColumnCounter;

	rhs.m_color = EColor::NoColor;
	rhs.m_name = "";
	rhs.m_BridgeCounter = NULL;
	rhs.m_ColumnCounter = NULL;

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

bool Player::HasBridgesToAdd() const
{
	return m_BridgeCounter > 0;
}

bool Player::HasColumnsToAdd() const
{
	return m_ColumnCounter > 0;
}

const uint16_t& Player::GetBridgeNumber() const noexcept
{
	return m_BridgeCounter;
}

const uint16_t& Player::GetColumnNumber() const noexcept
{
	return m_ColumnCounter;
}

void Player::SetColor(EColor rhs)
{
	m_color = rhs;
}

void Player::SetDoubleTurn(bool hasDoubleTurn)
{
	m_doubleTurn = hasDoubleTurn;
}

void Player::IncreaseBridgeNumber(const uint16_t& number)
{
	if(m_BridgeCounter + number <= 50) m_BridgeCounter += number;
}

void Player::DecreaseBridgeNumber(const uint16_t& number)
{
	if (m_BridgeCounter - number >= 0) m_BridgeCounter -= number;
}

void Player::IncreaseColumnNumber(const uint16_t& number)
{
	if (m_ColumnCounter + number <= 50) m_ColumnCounter += number;
}

void Player::DecreaseColumnNumber(const uint16_t& number)
{
	if (m_ColumnCounter - number >= 0) m_ColumnCounter -= number;
}
