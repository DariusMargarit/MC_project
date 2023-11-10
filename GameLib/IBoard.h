#pragma once

#include "IColumn.h"
#include "Position.h"

struct _declspec(dllexport) IBoard
{
	virtual IColumn* GetElement(Position pos) const = 0;

	virtual ~IBoard() = default;
};