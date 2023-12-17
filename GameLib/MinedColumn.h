#pragma once
#include "IColumn.h"
#include "Player.h"

class MinedColumn : public IColumn
{
public:
	MinedColumn() noexcept;
	MinedColumn(const MinedColumn& rhs) noexcept;
	MinedColumn(MinedColumn&& rhs) noexcept = default;
	~MinedColumn();
	MinedColumn& operator=(const MinedColumn& rhs) noexcept;
	MinedColumn& operator=(MinedColumn&& rhs) noexcept = default;

	IPlayer* GetPlayer() const noexcept override;
private:
	IPlayer* m_mine;
};

