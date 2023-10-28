#include "Column.h"

Column::Column(const EPlayer& Player)
	:m_Player{Player}
{}

Column::Column(const Column& otherColumn)
	:m_Player{otherColumn.GetPlayer()}
{}

Column::~Column()
{}

const EPlayer Column::GetPlayer() const
{
	return EPlayer();
}

Column& Column::operator=(const IColumn& otherColumn)
{
}
