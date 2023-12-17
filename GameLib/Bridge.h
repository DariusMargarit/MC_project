#pragma once

#include "IColumn.h"

class Bridge
{
public:
	Bridge(IColumn* lhs, IColumn* rhs);
	Bridge(const Bridge& rhs);
	Bridge(Bridge&& rhs) noexcept;
	~Bridge() = default;

    IColumn* GetFirstColumn() const noexcept;
	IColumn* GetSecondColumn() const noexcept;

	Bridge& operator=(const Bridge& rhs) noexcept;
	Bridge& operator=(Bridge&& rhs ) noexcept;

private:
	IColumn* m_firstColumn, * m_secondColumn;
};