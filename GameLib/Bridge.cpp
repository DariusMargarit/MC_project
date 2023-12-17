#include "Bridge.h"

Bridge::Bridge(IColumn* lhs, IColumn* rhs)
	: m_firstColumn{lhs}
	, m_secondColumn{rhs}
{
	// Empty
}


 IColumn* Bridge::GetFirstColumn() const noexcept
{
	return m_firstColumn;
}

 IColumn* Bridge::GetSecondColumn() const noexcept
{
	return m_secondColumn;
}


Bridge::Bridge(const Bridge& rhs)
{
	if (rhs.m_firstColumn)
		this->m_firstColumn = rhs.m_firstColumn;
	else
		this->m_firstColumn = nullptr;
	if (rhs.m_secondColumn)
		this->m_secondColumn = rhs.m_secondColumn;
	else
		this->m_secondColumn = nullptr;
	
}

Bridge::Bridge(Bridge&& rhs) noexcept
{
	if (rhs.m_firstColumn)
		this->m_firstColumn = rhs.m_firstColumn;
	else
		this->m_firstColumn = nullptr;
	if (rhs.m_secondColumn)
		this->m_secondColumn = rhs.m_secondColumn;
	else
		this->m_secondColumn = nullptr;

	rhs.m_firstColumn = nullptr;
	rhs.m_secondColumn = nullptr;
}

Bridge& Bridge::operator=(const Bridge& rhs) noexcept
{
	if (this == &rhs)
		return *this;

	if (rhs.m_firstColumn)
		m_firstColumn = rhs.m_firstColumn;
	else
		m_firstColumn = nullptr;

	if (rhs.m_secondColumn)
		m_secondColumn = rhs.m_secondColumn;
	else
		m_secondColumn = nullptr;

	return *this;
}

Bridge& Bridge::operator=(Bridge&& rhs) noexcept
{
	if (this == &rhs)
	{
		rhs.m_firstColumn = nullptr;
		rhs.m_secondColumn = nullptr;
		return *this;
	}

	if (rhs.m_firstColumn)
		m_firstColumn = rhs.m_firstColumn;
	else
		m_firstColumn = nullptr;

	if (rhs.m_secondColumn)
		m_secondColumn = rhs.m_secondColumn;
	else
		m_secondColumn = nullptr;

	rhs.m_firstColumn = nullptr;
	rhs.m_secondColumn = nullptr;

	return *this;
}





