#pragma once
#include <vector>
#include "IColumn.h"
#include "Bridge.h"

class Board {
private:
	std::vector<IColumn*> m_Columns;
	std::vector<Bridge*> m_Bridges;
	// board matrix
};