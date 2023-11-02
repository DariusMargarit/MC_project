#include "Bridge.h"

Bridge::Bridge(IColumn& firstColumn, IColumn& secondColumn)
	: m_FirstColumn{&firstColumn}
	, m_SecondColumn{&secondColumn}
{
}


const IColumn* Bridge::GetFirstColumn() const
{
	return m_FirstColumn;
}

const IColumn* Bridge::GetSecondColumn() const
{
	return m_SecondColumn;
}




