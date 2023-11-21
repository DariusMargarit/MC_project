#include "GameScreen.h"

GameScreen::GameScreen(QWidget* parent)
	: QWidget(parent)
	, m_layout(new QGridLayout(this))
{
	IPlayer* firstPlayer = IPlayer::Produce("Player1", "RED");
	IPlayer* secondPlayer = IPlayer::Produce("Player2", "BLACK");
	uint16_t boardSize = 24;
	m_game = IGame::Produce(firstPlayer, secondPlayer, boardSize);

	m_board = new BoardWidget(*m_game->GetBoard(), this);

	m_layout->addWidget(m_board);
	setLayout(m_layout);
}
