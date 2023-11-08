module Board;

import Column;

bool Board::ValidPlaceColumn(Position& position) const
{
	if (std::find(m_columns.begin(), m_columns.end(), &position) != m_columns.end()) {
		return true;
	}
	return false;
}

Board::Board() {

}

Board::~Board() {
	for (int index = 0; index < m_columns.size(); index++) {
		delete m_columns[index];
	}
	for (int index1 = 0; index1 < m_matrix.size(); index1++) {
		for (int index2 = 0; index2 < m_matrix[index1].size(); index2++) {
			delete m_matrix[index1][index2];
		}
	}
}

void Board::PlaceColumn(Position& position, const EPlayer& player)
{
	if (ValidPlaceColumn(position)) {
		IColumn* newColumn = new Column(player);
		m_matrix[position.GetX()][position.GetY()] = newColumn;
		m_columns.push_back(&position);
	}
}

Board::Board(const Board& otherBoard) {
	for (Position* position : otherBoard.m_columns) {
		this->m_columns.push_back(position);
	}
	for (const auto& bridgePair : otherBoard.m_bridges) {
		this->m_bridges.push_back(std::make_pair(bridgePair.first, bridgePair.second));

	}

	for (const std::vector<IColumn*>& row : otherBoard.m_matrix) {
		std::vector<IColumn*> newRow;
		for (IColumn* column : row) {
			newRow.push_back(column);
		}
		this->m_matrix.push_back(newRow);
	}
}