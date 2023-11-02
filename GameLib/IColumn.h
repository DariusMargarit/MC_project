#pragma once

enum class EPlayer {
	FirstPlayer,
	SecondPlayer
};

class IColumn
{
public:
	virtual ~IColumn() = default;
	virtual const EPlayer& GetPlayer() const = 0;
};