#pragma once
#include"IColumn.h"
#include"Bridge.h"

class Column : public IColumn
{
public:
	Column(const EPlayer&);
	Column(const Column&);
	~Column();

	const EPlayer GetPlayer() const;
	Column& operator=(const Column&);
private:
	EPlayer m_Player;
};