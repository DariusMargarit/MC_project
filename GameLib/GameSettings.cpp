#include "GameSettings.h"

const size_t GameSettings::defaultTableSize{24};
const size_t GameSettings::defaultColumnLimit{50};
const size_t GameSettings::defaultBridgeLimit{50};
const std::string GameSettings::defaultFirstPlayerName{"Player1"};
const EColor GameSettings::defaultFirstPlayerColor{EColor::Blue};
const std::string GameSettings::defaultSecondPlayerName{"Player2"};
const EColor GameSettings::defaultSecondPlayerColor{EColor::Red};
GameSettings* GameSettings::instance{nullptr};

IGameSettings* IGameSettings::Produce()
{

	return GameSettings::GetInstance();
}

GameSettings* GameSettings::GetInstance()
{
	if (!instance)
	{
		instance = new GameSettings();
	}
	return instance;
}

GameSettings::GameSettings()
	: m_tableSize(defaultTableSize)
	, m_columnLimit(defaultColumnLimit)
	, m_bridgeLimit(defaultBridgeLimit)
	, m_firstPlayerName(defaultFirstPlayerName)
	, m_firstPlayerColor(defaultFirstPlayerColor)
	, m_secondPlayerName(defaultSecondPlayerName)
	, m_secondPlayerColor(defaultSecondPlayerColor)
{
	// Empty
}

void GameSettings::SetTableSize(uint16_t size)
{
	m_tableSize = size;
}

void GameSettings::SetColumnLimit(uint16_t limit)
{
	m_columnLimit = limit;
}

void GameSettings::SetBridgeLimit(uint16_t limit)
{
	m_bridgeLimit = limit;
}

void GameSettings::SetFirstPlayerName(std::string_view name)
{
	m_firstPlayerName = name;
}

void GameSettings::SetFirstPlayerColor(EColor color)
{
	m_firstPlayerColor = color;
}

void GameSettings::SetSecondPlayerName(std::string_view name)
{
	m_secondPlayerName = name;
}

void GameSettings::SetSecondPlayerColor(EColor color)
{
	m_secondPlayerColor = color;
}

const uint16_t GameSettings::GetTableSize() const noexcept
{
	return m_tableSize;
}

const uint16_t GameSettings::GetColumnLimit() const noexcept
{
	return m_columnLimit;
}

const uint16_t GameSettings::GetBridgeLimit() const noexcept
{
	return m_bridgeLimit;
}

const std::string_view GameSettings::GetFirstPlayerName() const noexcept
{
	return m_firstPlayerName;
}

const EColor GameSettings::GetFirstPlayerColor() const noexcept
{
	return m_firstPlayerColor;
}

const std::string_view GameSettings::GetSecondPlayerName() const noexcept
{
	return m_secondPlayerName;
}

const EColor GameSettings::GetSecondPlayerColor() const noexcept
{
	return m_secondPlayerColor;
}
