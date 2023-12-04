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
	static IPlayer* Produce(std::string_view name, EColor color);

	virtual EColor GetColor() const noexcept = 0;
	virtual std::string_view GetName() const noexcept = 0;

	virtual ~IPlayer() = default;
};