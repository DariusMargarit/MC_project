#pragma once

#include "Position.h"
#include "IPlayer.h"

struct _declspec(dllexport) IGame
{
	static IGame* Produce(IPlayer* player1, IPlayer* player2);

	virtual IPlayer* GetTurn() const = 0;

	virtual void PlaceColumn(Position position) = 0;
	virtual void MakeBridge(Position firstPosition, Position secondPosition) = 0;
	virtual void RemoveBridge(Position firstPosition, Position secondPosition) = 0;

	virtual ~IGame() = default;
};