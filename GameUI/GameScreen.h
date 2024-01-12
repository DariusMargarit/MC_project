#pragma once

#include "BoardWidget.h"
#include "PlayerBar.h"
#include "HistoryWidget.h"

#include "IGame.h"
#include "IGameObserver.h"

class GameScreen : public QWidget, public IGameObserver, public std::enable_shared_from_this<GameScreen>
{
	Q_OBJECT

public:
	GameScreen(IGamePtr game, QWidget* parent = nullptr);
	void SetWindowFullScreen(bool isFullScreen);

	void OnColumnPlaced(Position& position, IPlayer* player) override;
	void OnBridgePlaced(Position& firstPos, Position& secondPos, IPlayer* player) override;
	void OnBridgeRemoved(Position& firstPos, Position& secondPos, IPlayer* player) override;

private slots:
	void OnHistoryClicked(QListWidgetItem* item);
	void OnBoardClicked(const Position& position, const Qt::MouseButton& button);

private:
	QGridLayout* m_layout;
	BoardWidget* m_board;
	HistoryWidget* m_history;
	PlayerBar* m_firstPlayerBar, * m_secondPlayerBar;
	IGamePtr m_game;
	Position m_selectedColumnPos;
};

