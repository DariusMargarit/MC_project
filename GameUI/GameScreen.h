#pragma once

#include "BoardWidget.h"
#include "PlayerBar.h"
#include "HistoryWidget.h"

#include "IGame.h"

class GameScreen : public QWidget
{
	Q_OBJECT

public:
	GameScreen(QWidget* parent = nullptr);
	void SetWindowFullScreen(bool isFullScreen);

private slots:
	void OnBoardClicked(const Position& position, const Qt::MouseButton& button);

private:
	QGridLayout* m_layout;
	BoardWidget* m_board;
	HistoryWidget* m_history;
	PlayerBar* m_firstPlayerBar, * m_secondPlayerBar;
	IGame* m_game;
	Position m_selectedColumnPos;
};

