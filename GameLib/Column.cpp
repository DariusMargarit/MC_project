#include "Column.h"

Column::Column(const EPlayer& Player)
	:m_Player{Player}
{}

Column::Column(const Column& otherColumn)
	:m_Player{otherColumn.GetPlayer()}
{}

Column::~Column()
{}

const EPlayer& Column::GetPlayer() const
{
	return m_Player;
}

Column& Column::operator=(const Column& otherColumn)
{
	if (this->GetPlayer() != otherColumn.GetPlayer())
		this->m_Player = otherColumn.GetPlayer();
	return *this;
}
