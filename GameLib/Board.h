#pragma once
#include <vector>
#include "IColumn.h"
#include "Bridge.h"
#include "API/Position.h"
#include "Column.h"

class Board {
private:
	std::vector<Position*> m_columns;
	std::vector<std::pair<Position*, Position*>> m_bridges;
	std::vector<std::vector<IColumn*>> m_matrix;
	bool ValidPlaceColumn(Position&) const;
public:
	Board();
	Board(const Board&);
	~Board();
	void PlaceColumn(Position&, const EPlayer&);
};