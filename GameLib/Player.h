#pragma once

#include "IPlayer.h"

class _declspec(dllexport) Player : public IPlayer
{
public:
	Player(const std::string_view& name, const EColor& color);
	Player(const Player* other);
	Player(Player&& other) noexcept;
	Player& operator= (const Player* other) noexcept;
	Player& operator= (Player&& other) noexcept;

	EColor GetColor() const noexcept override;
	std::string_view GetName() const noexcept override;

private:
	std::string m_name;
	EColor m_color;
};
