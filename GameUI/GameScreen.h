#pragma once

#include "Board.h"

class GameScreen : public QWidget
{
	Q_OBJECT

public:
	GameScreen(QWidget* parent = nullptr);

private:
	QGridLayout* m_layout;
	Board* m_board;
};

