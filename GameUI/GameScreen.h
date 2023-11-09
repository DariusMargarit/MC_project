#pragma once

#include "Board.h"

class GameScreen : public QWidget
{
public:
	GameScreen(QWidget* parent = nullptr);
private:
	QGridLayout* m_layout;
	Board* m_board;
};

