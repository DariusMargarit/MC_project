#include "Board.h"

Board::Board(uint32_t size)
{
	m_layout = new QGridLayout();
	InitializeButtons(size);

}

void Board::InitializeButtons(uint32_t size)
{
	m_buttons.resize(size);
	for (int row = 0; row < size; row++)
	{
		m_buttons[row].resize(size);
		for (int column = 0; column < size; column++)
		{
			m_buttons[row][column] = new BoardButton();
			m_layout->addWidget(m_buttons[row][column], row, column);
		}
	}
	this->setLayout(m_layout);
}
