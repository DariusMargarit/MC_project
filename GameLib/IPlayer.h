#pragma once

#include <string_view>

struct _declspec(dllexport) IPlayer
{
	static IPlayer* Produce(std::string_view name, std::string_view color);

	virtual std::string_view GetColor() const = 0;
	virtual std::string_view GetName() const = 0;

	virtual ~IPlayer() = default;
};