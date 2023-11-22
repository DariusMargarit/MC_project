#pragma once

#include "IColumn.h"
#include "Position.h"

struct _declspec(dllexport) IBoard
{
	virtual const uint16_t GetSize() const = 0;

	virtual const IColumn* GetElement(Position pos) const = 0;
	virtual const IColumn* GetElement(uint16_t row, uint16_t column) const = 0;

	virtual const IColumn* operator[](Position pos) const = 0;

	virtual ~IBoard() = default;
};