#pragma once
#include "BoardButton.h"
class Board : public QWidget
{
private:
	std::vector<std::vector<BoardButton*>> buttons;
};

