#include "GameScreen.h"

GameScreen::GameScreen(QWidget* parent)
	: QWidget(parent)
	, m_layout(new QGridLayout(this))
{

	IPlayer* firstPlayer = IPlayer::Produce("Player1", EColor::Red);
	IPlayer* secondPlayer = IPlayer::Produce("Player2", EColor::Blue);
	uint16_t boardSize = 24;
	m_game = IGame::Produce(firstPlayer, secondPlayer, boardSize);

	m_board = new BoardWidget(*m_game->GetBoard(), firstPlayer->GetColor(), secondPlayer->GetColor(), this);

	m_layout->addWidget(m_board);
	setLayout(m_layout);

	connect(m_board, &BoardWidget::BoardClicked, this, &GameScreen::OnBoardClicked);
}

void GameScreen::OnBoardClicked(const Position& position)
{
	m_game->PlaceColumn(position);
}
