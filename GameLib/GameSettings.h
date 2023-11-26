#pragma once

#include "IGameSettings.h"

class GameSettings : public IGameSettings
{
public:
// Make a new instance of GameSettings with singleton
	static GameSettings* ObtainInstance();

// Board settings

	// Getters
	virtual const uint16_t GetTableSize() const noexcept override;
	virtual const uint16_t GetColumnLimit() const noexcept override;
	virtual const uint16_t GetBridgeLimit() const noexcept override;
	// Setters
	virtual void SetTableSize(uint16_t size) override;
	virtual void SetColumnLimit(uint16_t limit) override;
	virtual void SetBridgeLimit(uint16_t limit) override;

// Player settings

	// Getters
	virtual const std::string_view GetFirstPlayerName() const noexcept override;
	virtual const EColor GetFirstPlayerColor() const noexcept override;
	virtual const std::string_view GetSecondPlayerName() const noexcept override;
	virtual const EColor GetSecondPlayerColor() const noexcept override;
	// Setters
	virtual void SetFirstPlayerName(std::string_view name) override;
	virtual void SetFirstPlayerColor(EColor color) override;
	virtual void SetSecondPlayerName(std::string_view name) override;
	virtual void SetSecondPlayerColor(EColor color) override;


private:
	GameSettings();
	uint16_t m_tableSize, m_columnLimit, m_bridgeLimit;
	std::string m_firstPlayerName, m_secondPlayerName;
	EColor m_firstPlayerColor, m_secondPlayerColor;

	static const size_t defaultTableSize;
	static const size_t defaultColumnLimit;
	static const size_t defaultBridgeLimit;
	static const std::string defaultFirstPlayerName;
	static const EColor defaultFirstPlayerColor;
	static const std::string defaultSecondPlayerName;
	static const EColor defaultSecondPlayerColor;

	static GameSettings* instance;


};

