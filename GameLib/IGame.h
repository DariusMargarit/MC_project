#pragma once

#include "IGameSettings.h"
#include "Position.h"
#include "IPlayer.h"
#include "IBoard.h"

struct IGame
{
	static IGame* Produce(const IGameSettings& settings);

	virtual IPlayer* GetTurn() const = 0;
	virtual IBoard* GetBoard() const = 0;

	virtual IPlayer* GetFirstPlayer() const = 0;
	virtual IPlayer* GetSecondPlayer() const = 0;

	virtual void PlaceColumn(Position position) = 0;
	virtual void MakeBridge(Position firstPosition, Position secondPosition) = 0;
	virtual void RemoveBridge(Position firstPosition, Position secondPosition) = 0;

	virtual ~IGame() = default;
};