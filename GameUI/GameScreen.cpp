#include "GameScreen.h"

GameScreen::GameScreen(QWidget* parent)
	: QWidget(parent)
	, m_board(new Board(24, this))
	, m_layout(new QGridLayout(this))
{
	m_layout->addWidget(m_board);
	setLayout(m_layout);
}
