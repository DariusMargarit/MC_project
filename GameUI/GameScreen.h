#pragma once
#include "Board.h"
#include "IGame.h"

class GameScreen : public QWidget
{
public:
	GameScreen(QWidget* parent = nullptr);
private:
	QGridLayout* m_layout;
	Board* m_board;
};

