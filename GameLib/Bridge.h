#pragma once
#include "IColumn.h"

enum class EPlayer {
	FirstPlayer,
	SecondPlayer
};

class Bridge {
private:
	EPlayer m_Player;
	IColumn* m_FirstColumn, *m_SecondColumn;
};