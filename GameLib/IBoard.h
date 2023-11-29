#pragma once

#include "IColumn.h"
#include "Position.h"

struct _declspec(dllexport) IBoard
{
	virtual const uint16_t GetSize() const = 0;

	virtual const IColumn* GetElement(const Position& pos) const = 0;
	virtual const IColumn* GetElement(const uint16_t& row, const uint16_t& column) const = 0;

	virtual const IColumn* operator[](Position pos) const = 0;

	virtual ~IBoard() = default;
};