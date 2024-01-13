#include "BulldozerColumn.h"

Player* BulldozerColumn::m_bulldozer{ new Player("Bulldozer", EColor::Yellow, 0, 0) };

IPlayer* BulldozerColumn::GetPlayer() const noexcept
{
    return m_bulldozer;
}
