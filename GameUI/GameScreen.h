#pragma once

#include "BoardWidget.h"
#include "../GameLib/IGame.h"

class GameScreen : public QWidget
{
	Q_OBJECT

public:
	GameScreen(QWidget* parent = nullptr);
	
public slots:
	void OnBoardClicked(const Position& position);


private:
	QGridLayout* m_layout;
	BoardWidget* m_board;
	IGame* m_game;
};

