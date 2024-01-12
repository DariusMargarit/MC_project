#pragma once
#include "IColumn.h"
#include "Player.h"

class MinedColumn : public IColumn
{
public:
	MinedColumn() noexcept = default;
	MinedColumn(const MinedColumn& other) noexcept = default;
	MinedColumn(MinedColumn&& other) noexcept = default;
	~MinedColumn() = default;
	MinedColumn& operator=(const MinedColumn& rhs) noexcept = default;
	MinedColumn& operator=(MinedColumn&& rhs) noexcept = default;

	IPlayer* GetPlayer() const noexcept override;
private:
	static Player* mineSpot;
};

