#include "Board.h"

Board::Board() {

}

Board::~Board() {
	for (int index = 0; index < m_Columns.size(); index++) {
		delete m_Columns[index];
	}
	for (int index = 0; index < matrix.size(); index++) {
		delete matrix[index];
	}
}