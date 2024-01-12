#include "MinedColumn.h"

Player* MinedColumn::mineSpot{ new Player("", EColor::NoColor)};

IPlayer* MinedColumn::GetPlayer() const noexcept
{
    return mineSpot;
}
