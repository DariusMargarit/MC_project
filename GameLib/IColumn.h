#pragma once

class IColumn
{
	IColumn() = default;
	virtual IColumn& operator=(const IColumn& other) = 0;
	virtual ~IColumn() = default;
};