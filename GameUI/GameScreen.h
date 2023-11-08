#pragma once

#include "Board.h"

import IGame;

class GameScreen : public QWidget
{
public:
	GameScreen(QWidget* parent = nullptr);
private:
	QGridLayout* m_layout;
	Board* m_board;
	IGame* game;
};

