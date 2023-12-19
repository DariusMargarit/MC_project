#include "BulldozerColumn.h"

BulldozerColumn::BulldozerColumn() noexcept
{
    m_bulldozer = new Player("", EColor::NoColor);
}

BulldozerColumn::BulldozerColumn(const BulldozerColumn& rhs) noexcept
    :m_bulldozer{ rhs.m_bulldozer }
{
}

BulldozerColumn::~BulldozerColumn()
{
    delete m_bulldozer;
}

BulldozerColumn& BulldozerColumn::operator=(const BulldozerColumn& rhs) noexcept
{
    if (m_bulldozer != rhs.m_bulldozer)
        m_bulldozer = rhs.m_bulldozer;
    return *this;
}

IPlayer* BulldozerColumn::GetPlayer() const noexcept
{
    return m_bulldozer;
}
