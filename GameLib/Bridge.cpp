#include "Bridge.h"

Bridge::Bridge(IColumn* firstColumn, IColumn* secondColumn)
	: m_firstColumn{firstColumn}
	, m_secondColumn{secondColumn}
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


Bridge::Bridge(const Bridge& otherBridge)
{
	if (otherBridge.m_firstColumn)
		this->m_firstColumn = otherBridge.m_firstColumn;
	else
		this->m_firstColumn = nullptr;
	if (otherBridge.m_secondColumn)
		this->m_secondColumn = otherBridge.m_secondColumn;
	else
		this->m_secondColumn = nullptr;
	
}

Bridge::Bridge(Bridge&& otherBridge) noexcept
{
	if (otherBridge.m_firstColumn)
		this->m_firstColumn = otherBridge.m_firstColumn;
	else
		this->m_firstColumn = nullptr;
	if (otherBridge.m_secondColumn)
		this->m_secondColumn = otherBridge.m_secondColumn;
	else
		this->m_secondColumn = nullptr;

	otherBridge.m_firstColumn = nullptr;
	otherBridge.m_secondColumn = nullptr;
}

Bridge& Bridge::operator=(const Bridge& otherBridge) noexcept
{
	if (this == &otherBridge)
		return *this;

	if (otherBridge.m_firstColumn)
		m_firstColumn = otherBridge.m_firstColumn;
	else
		m_firstColumn = nullptr;

	if (otherBridge.m_secondColumn)
		m_secondColumn = otherBridge.m_secondColumn;
	else
		m_secondColumn = nullptr;

	return *this;
}

Bridge& Bridge::operator=(Bridge&& otherBridge) noexcept
{
	if (this == &otherBridge)
	{
		otherBridge.m_firstColumn = nullptr;
		otherBridge.m_secondColumn = nullptr;
		return *this;
	}

	if (otherBridge.m_firstColumn)
		m_firstColumn = otherBridge.m_firstColumn;
	else
		m_firstColumn = nullptr;

	if (otherBridge.m_secondColumn)
		m_secondColumn = otherBridge.m_secondColumn;
	else
		m_secondColumn = nullptr;

	otherBridge.m_firstColumn = nullptr;
	otherBridge.m_secondColumn = nullptr;

	return *this;
}





