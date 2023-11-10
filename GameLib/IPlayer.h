#pragma once

#include <string_view>

struct _declspec(dllexport) IPlayer
{
	virtual std::string_view GetColor() const = 0;
	virtual std::string_view GetName() const = 0;

	virtual ~IPlayer() = default;
};