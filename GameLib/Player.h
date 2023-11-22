#pragma once

#include "IPlayer.h"

class _declspec(dllexport) Player : public IPlayer
{
public:
	Player(std::string_view name, EColor color);
	Player(const Player* other);
	Player(Player&& other) noexcept;
	Player& operator= (const Player* other);
	Player& operator= (Player&& other) noexcept;

	EColor GetColor() const override;
	std::string_view GetName() const override;

private:
	std::string m_name;
	EColor m_color;
};
