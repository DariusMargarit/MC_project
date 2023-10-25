#pragma once
#include "IGame.h"
#include "Board.h"

class Game : public IGame {
private:
	Board m_Board;
	uint16_t m_ColumnSize;

public:

};