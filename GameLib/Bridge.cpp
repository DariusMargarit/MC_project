#include "Bridge.h"

Bridge::Bridge(IColumn& firstColumn, IColumn& secondColumn)
	: m_firstColumn{&firstColumn}
	, m_secondColumn{&secondColumn}
{
}


const IColumn* Bridge::GetFirstColumn() const
{
	return m_firstColumn;
}

const IColumn* Bridge::GetSecondColumn() const
{
	return m_secondColumn;
}




