#pragma once
#include"IColumn.h"


class Column : public IColumn
{
public:
	Column(const EPlayer&);
	Column(const Column&);
	~Column();

	Column& operator=(const Column&);

	const EPlayer& GetPlayer() const override;

private:
	EPlayer m_player;
};