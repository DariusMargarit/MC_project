#include "MinedColumn.h"

Player* MinedColumn::mineSpot{ new Player("", EColor::NoColor, 0, 0)};

IPlayer* MinedColumn::GetPlayer() const noexcept
{
    return mineSpot;
}
