#pragma once
#include "Board.h"
#include "IGame.h"

class GameScreen
{
public:
	GameScreen(QWidget* parent = nullptr);
private:
	Board* m_board;
};

