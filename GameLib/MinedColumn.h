#pragma once
#include "IColumn.h"

class MinedColumn : public IColumn
{
public:
	MinedColumn() = default;
	MinedColumn(const MinedColumn& other) noexcept = default;
	MinedColumn(MinedColumn&& other) noexcept = default;
	~MinedColumn() = default;
	MinedColumn& operator=(const MinedColumn& other) noexcept = default;
	MinedColumn& operator=(MinedColumn&& other) noexcept = default;

	IPlayer* GetPlayer() const noexcept override;
};

