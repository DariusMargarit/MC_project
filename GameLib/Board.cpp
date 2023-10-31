#include "Board.h"

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

Board::Board(const Board& otherBoard) {
	// copy constructor
}