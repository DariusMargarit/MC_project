#pragma once

#include "IColumn.h"

class Bridge {
public:
	Bridge(IColumn& firstColumn,IColumn& secondColumn);
	~Bridge() = default;

	const IColumn* GetFirstColumn() const;
	const IColumn* GetSecondColumn() const;
	Bridge(const Bridge& otherBridge);
	Bridge& operator=(const Bridge& otherBridge);



private:
	IColumn* m_firstColumn, *m_secondColumn;
};