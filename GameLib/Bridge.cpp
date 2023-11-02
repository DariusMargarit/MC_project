#include "Bridge.h"

Bridge::Bridge(IColumn& firstColumn, IColumn& secondColumn)
	: m_FirstColumn{&firstColumn}
	, m_SecondColumn{&secondColumn}
{
}
