#pragma once

#include "BoardWidget.h"
#include "../GameLib/IGame.h"

class GameScreen : public QWidget
{
	Q_OBJECT

public:
	GameScreen(QWidget* parent = nullptr);
	
private slots:
	void OnBoardClicked(const Position& position, const Qt::MouseButton& button);

private:
	QGridLayout* m_layout;
	BoardWidget* m_board;
	IGame* m_game;
	Position m_selectedColumnPos;
};

