#include "GameScreen.h"

GameScreen::GameScreen(QWidget* parent)
{
	m_board = new Board(24);
	m_layout = new QGridLayout();
	m_layout->addWidget(m_board);
	setLayout(m_layout);
}
