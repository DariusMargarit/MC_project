#pragma once

#include "IColumn.h"

class Bridge
{
public:
	Bridge(IColumn* firstColumn, IColumn* secondColumn);
	Bridge(const Bridge& otherBridge);
	Bridge(Bridge&& otherBridge) noexcept;
	~Bridge() = default;

    IColumn* GetFirstColumn() const noexcept;
	IColumn* GetSecondColumn() const noexcept;

	Bridge& operator=(const Bridge& otherBridge) noexcept;
	Bridge& operator=(Bridge&& otherBridge) noexcept;

private:
	IColumn* m_firstColumn, * m_secondColumn;
};