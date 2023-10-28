#pragma once
#include"IColumn.h"
class Column : public IColumn
{
public:
	Column();
	Column(const Column&);
	~Column();
	Column& operator=(const IColumn&) override;
};