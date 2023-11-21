#pragma once

#include "BoardWidget.h"
#include "../GameLib/IGame.h"

class GameScreen : public QWidget
{
	Q_OBJECT

public:
	GameScreen(QWidget* parent = nullptr);

private:
	QGridLayout* m_layout;
	BoardWidget* m_board;
	IGame* m_game;
};

