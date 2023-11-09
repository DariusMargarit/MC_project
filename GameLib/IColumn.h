#pragma once

enum class _declspec(dllexport) EPlayer {
	FirstPlayer,
	SecondPlayer
};

struct _declspec(dllexport) IColumn
{
	virtual ~IColumn() = default;
	virtual const EPlayer& GetPlayer() const = 0;
};