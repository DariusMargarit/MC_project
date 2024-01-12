#include "BulldozerColumn.h"

Player* BulldozerColumn::m_bulldozer{ new Player("", EColor::NoColor, 0, 0) };

IPlayer* BulldozerColumn::GetPlayer() const noexcept
{
    return m_bulldozer;
}
