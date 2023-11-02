#pragma once

enum class EPlayer {
	FirstPlayer,
	SecondPlayer
};

struct IColumn
{
	virtual ~IColumn() = default;
	virtual const EPlayer& GetPlayer() const = 0;
};