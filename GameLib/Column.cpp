#include "Column.h"

Column::Column(const EPlayer& Player)
	:m_player{Player}
{}

Column::Column(const Column& otherColumn)
	:m_player{otherColumn.GetPlayer()}
{}

Column::~Column()
{}

const EPlayer& Column::GetPlayer() const
{
	return m_player;
}

Column& Column::operator=(const Column& otherColumn)
{
	if (this->GetPlayer() != otherColumn.GetPlayer())
		this->m_player = otherColumn.GetPlayer();
	return *this;
}
