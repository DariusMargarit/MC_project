#pragma once

#include <memory>

#include "IPlayer.h"

struct _declspec(dllexport) IGameSettings
{

// Make a new instance of GameSettings with singleton
	static IGameSettings* Produce();

// Board settings

	// Getters
	virtual const uint16_t GetTableSize() const noexcept = 0;
	virtual const uint16_t GetColumnLimit() const noexcept = 0;
	virtual const uint16_t GetBridgeLimit() const noexcept = 0;
	// Setters
	virtual void SetTableSize(uint16_t size) = 0;
	virtual void SetColumnLimit(uint16_t limit) = 0;
	virtual void SetBridgeLimit(uint16_t limit) = 0;

// Player settings

	// Getters
	virtual const std::string_view GetFirstPlayerName() const noexcept = 0;
	virtual const EColor GetFirstPlayerColor() const noexcept = 0;
	virtual const std::string_view GetSecondPlayerName() const noexcept = 0;
	virtual const EColor GetSecondPlayerColor() const noexcept = 0;
	// Setters
	virtual void SetFirstPlayerName(std::string_view name) = 0;
	virtual void SetFirstPlayerColor(EColor color) = 0;
	virtual void SetSecondPlayerName(std::string_view name) = 0;
	virtual void SetSecondPlayerColor(EColor color) = 0;

	virtual ~IGameSettings() = default;

};

