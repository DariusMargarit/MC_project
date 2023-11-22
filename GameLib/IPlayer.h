#pragma once

#include <string_view>

enum class EColor 
{
	Red,
	Blue,
	NoColor,
};

struct _declspec(dllexport) IPlayer
{
	static IPlayer* Produce(std::string_view name, EColor color);

	virtual EColor GetColor() const = 0;
	virtual std::string_view GetName() const = 0;

	virtual ~IPlayer() = default;
};