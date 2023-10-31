#pragma once
#include <vector>
#include "IColumn.h"
#include "Bridge.h"
#include "API/Position.h"

class Board {
private:
	std::vector<Position*> m_Columns;
	std::vector<std::pair<Position*, Position*>> m_Bridges;
	std::vector<std::vector<IColumn*>> matrix;

public:
	Board();
	Board(const Board&);
	~Board();
};