#include "MinedColumn.h"

MinedColumn::MinedColumn()
{
    m_mine = new Player("",EColor::NoColor);
}

MinedColumn::MinedColumn(const MinedColumn& rhs) noexcept
    :m_mine{ rhs.m_mine }
{
}

MinedColumn::~MinedColumn()
{
    delete m_mine;
}

MinedColumn& MinedColumn::operator=(const MinedColumn& rhs) noexcept
{
    if (m_mine != rhs.m_mine)
        m_mine = rhs.m_mine;
    return *this;
}

IPlayer* MinedColumn::GetPlayer() const noexcept
{
    return m_mine;
}
