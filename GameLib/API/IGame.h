#pragma once

#include "Position.h"

class IGame {
	virtual void PlaceColumn(Position position) = 0;
	virtual void MakeBridge(Position firstPosition, Position secondPosition) = 0;
	virtual void RemoveBridge(Position firstPosition, Position secondPosition) = 0;

	virtual ~IGame() = default;
};