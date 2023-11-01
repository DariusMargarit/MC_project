#include "Board.h"

bool Board::ValidPlaceColumn(Position& position) const
{
	if (std::find(m_Columns.begin(), m_Columns.end(), &position) != m_Columns.end()) {
		return true;
	}
	return false;
}

Board::Board() {

}

Board::~Board() {
	for (int index = 0; index < m_Columns.size(); index++) {
		delete m_Columns[index];
	}
	for (int index1 = 0; index1 < matrix.size(); index1++) {
		for (int index2 = 0; index2 < matrix[index1].size(); index2++) {
			delete matrix[index1][index2];
		}
	}
}

void Board::PlaceColumn(Position& position, const EPlayer& player)
{
	if (ValidPlaceColumn(position)) {
		IColumn* newColumn = new Column(player);
		matrix[position.GetX()][position.GetY()] = newColumn;
		m_Columns.push_back(&position);
	}
}

Board::Board(const Board& otherBoard) {
	// copy constructor
}