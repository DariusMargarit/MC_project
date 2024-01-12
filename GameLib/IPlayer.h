#pragma once

#include <string_view>

enum class EColor 
{
	Red,
	Blue,
	Pink,
	Purple,
	Yellow,
	Orange,
	NoColor,
};

struct IPlayer
{
	virtual EColor GetColor() const noexcept = 0;
	virtual std::string_view GetName() const noexcept = 0;
	virtual void SetColor(EColor rhs) = 0;
	virtual ~IPlayer() = default;
};