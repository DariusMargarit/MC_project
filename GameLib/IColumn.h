#pragma once

class IColumn
{
public:
	IColumn() = default;
	virtual IColumn& operator=(const IColumn& other) = 0;
	virtual ~IColumn() = default;
};