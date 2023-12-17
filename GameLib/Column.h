#pragma once

#include "IColumn.h"

class Column : public IColumn
{
public:
	Column(IPlayer* player);
	Column(const Column& rhs);
	Column(Column&& other) noexcept;
	Column& operator=(const Column& rhs) noexcept;
	Column& operator=(Column&& rhs) noexcept;

	IPlayer* GetPlayer() const noexcept override;

private:
	IPlayer* m_player;
};