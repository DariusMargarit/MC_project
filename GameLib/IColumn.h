#pragma once

#include "IPlayer.h"

struct IColumn
{
	virtual IPlayer* GetPlayer() const noexcept = 0;

	virtual ~IColumn() = default;
};