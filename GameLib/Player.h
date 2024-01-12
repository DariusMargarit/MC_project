#pragma once

#include "IPlayer.h"

class Player : public IPlayer
{
public:
	Player(const std::string_view& name, const EColor& color);
	Player(const Player* rhs);
	Player(Player&& rhs) noexcept;
	Player& operator= (const Player* rhs) noexcept;
	Player& operator= (Player&& rhs) noexcept;

	EColor GetColor() const noexcept override;
	std::string_view GetName() const noexcept override;
	bool GetDoubleTurn() const;

	void SetColor(EColor rhs) override;
	void SetDoubleTurn(bool hasDoubleTurn);

private:
	bool m_doubleTurn;
	std::string m_name;
	EColor m_color;
};
