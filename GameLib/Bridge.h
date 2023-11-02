#pragma once

#include "IColumn.h"

class Bridge {
public:
	Bridge(IColumn& firstColumn,IColumn& secondColumn);
	~Bridge() = default;

	const IColumn* GetFirstColumn() const;
	const IColumn* GetSecondColumn() const;




private:
	IColumn* m_FirstColumn, *m_SecondColumn;
};