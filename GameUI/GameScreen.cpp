#include "GameScreen.h"

#include "../GameLib/IGameSettings.h"

GameScreen::GameScreen(QWidget* parent)
	: QWidget(parent)
	, m_layout(new QGridLayout(this))
{

	IGameSettings* settings = IGameSettings::GetInstance();
	m_game = IGame::Produce(*settings);

	m_board = new BoardWidget(*m_game->GetBoard(), settings->GetFirstPlayerColor(), settings->GetSecondPlayerColor(), this);

	m_layout->addWidget(m_board);
	setLayout(m_layout);

	connect(m_board, SIGNAL(BoardClicked(const Position&)), SLOT(OnBoardClicked(const Position&)));
}

void GameScreen::OnBoardClicked(const Position& position)
{
	m_game->PlaceColumn(position);
}
