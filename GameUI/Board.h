#pragma once

#include <QGridLayout>

#include "BoardButton.h"

class Board : public QWidget
{
public:
	Board(uint32_t size);
	void InitializeButtons(uint32_t size);

private:
	QGridLayout* m_layout;
	std::vector<std::vector<BoardButton*>> m_buttons;
};

