#pragma once

#include "IColumn.h"

class Bridge {
public:
	Bridge(IColumn& firstColumn,IColumn& secondColumn);

private:
	EPlayer m_Player;
	IColumn* m_FirstColumn, *m_SecondColumn;
};