#pragma once

#include "IColumn.h"

class Bridge
{
public:
	Bridge(IColumn* firstColumn,IColumn* secondColumn);
	Bridge(const Bridge& otherBridge);
	Bridge(Bridge&& otherBridge) noexcept;
	~Bridge() = default;

    IColumn* GetFirstColumn() const;
	IColumn* GetSecondColumn() const;

	bool HasPositions( IColumn* pos1,IColumn* pos2) const;

	Bridge& operator=(const Bridge& otherBridge);
	Bridge& operator=(Bridge&& otherBridge) noexcept;

private:
	IColumn* m_firstColumn, * m_secondColumn;
};