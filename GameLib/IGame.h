#pragma once

#include "Position.h"

struct _declspec(dllexport) IGame
{
public:
	static IGame* Produce();

	virtual void PlaceColumn(Position position) = 0;
	virtual void MakeBridge(Position firstPosition, Position secondPosition) = 0;
	virtual void RemoveBridge(Position firstPosition, Position secondPosition) = 0;

	virtual ~IGame() = default;
};