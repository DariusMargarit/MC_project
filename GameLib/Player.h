#pragma once

#include "IPlayer.h"

class Player : public IPlayer
{
public:
	Player(const std::string_view& name, const EColor& color,
		   const uint16_t& BridgeCounter = 50, const uint16_t& ColumnCounter = 50);
	Player(const Player* rhs);
	Player(Player&& rhs) noexcept;
	Player& operator= (const Player* rhs) noexcept;
	Player& operator= (Player&& rhs) noexcept;

	EColor GetColor() const noexcept override;
	std::string_view GetName() const noexcept override;
	const uint16_t& GetBridgeNumber() const noexcept;
	const uint16_t& GetColumnNumber() const noexcept;

	bool GetDoubleTurn() const;
	bool HasBridgesToAdd() const;
	bool HasColumnsToAdd() const;

	void SetColor(EColor rhs) override;
	void SetDoubleTurn(bool hasDoubleTurn);
	void IncreaseBridgeNumber(const uint16_t& number = 1);
	void IncreaseColumnNumber(const uint16_t& number = 1);
	void DecreaseBridgeNumber(const uint16_t& number = 1);
	void DecreaseColumnNumber(const uint16_t& number = 1);

private:
	bool m_doubleTurn;
	std::string m_name;
	EColor m_color;
	uint16_t m_BridgeCounter;
	uint16_t m_ColumnCounter;
};
