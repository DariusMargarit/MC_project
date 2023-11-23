#include "Board.h"
#include "Column.h"

Board::Board(uint16_t size)
	: m_matrix{size, std::vector<IColumn*>(size, nullptr)}
{
	// Empty
}

bool Board::ValidPlaceColumn(Position position) const
{
	if (m_matrix[position.GetRow()][position.GetColumn()] != nullptr)
	{
		return false;
	}
	return true;
}

std::vector<std::vector<IColumn*>> Board::BridgeSurroundingMatrix(Position& firstPosition, Position& secondPosition) const
{
	std::vector<std::vector<IColumn*>>surroundingMatrix;
	uint16_t lowerRowIndex = std::min(firstPosition.GetRow(), secondPosition.GetRow());
	uint16_t lowerColumnIndex = std::min(firstPosition.GetColumn(), secondPosition.GetColumn());
	uint16_t absRowValue = abs(firstPosition.GetRow() - secondPosition.GetRow());
	lowerRowIndex = std::max<uint16_t>(--lowerRowIndex, 0);
	lowerColumnIndex = std::max<uint16_t>(--lowerColumnIndex, 0);

	std::vector<IColumn*>row;
	uint16_t higherRowIndex, higherColumnIndex;
	if (absRowValue == 1) 
	{
		higherRowIndex = std::min<uint16_t>(lowerRowIndex + 3, m_matrix.size() - 1);
		higherColumnIndex = std::min<uint16_t>(lowerColumnIndex + 4, m_matrix[0].size() - 1);
	} else 
	{
		uint16_t higherRowIndex = std::min<uint16_t>(lowerRowIndex + 4, m_matrix.size() - 1);
		uint16_t higherColumnIndex = std::min<uint16_t>(lowerColumnIndex + 3, m_matrix[0].size() - 1);
	}
	for (uint16_t rowIndex = lowerRowIndex; rowIndex < higherRowIndex; ++rowIndex)
	{
		for (uint16_t columnIndex = lowerColumnIndex; columnIndex < higherColumnIndex; ++columnIndex)
		{
			row.push_back(m_matrix[rowIndex][columnIndex]);
		}
		surroundingMatrix.push_back(row);
		row.clear();
	}
	surroundingMatrix[0][0] = nullptr;
	surroundingMatrix[0][surroundingMatrix[0].size() - 1] = nullptr;
	surroundingMatrix[surroundingMatrix.size() - 1][0] = nullptr;
	surroundingMatrix[surroundingMatrix.size() - 1][surroundingMatrix[0].size() - 1] = nullptr;

	return surroundingMatrix;
}

bool Board::ValidBridge(Position firstPosition, Position secondPosition) const
{
	uint16_t absRowValue = abs(firstPosition.GetRow() - secondPosition.GetRow());
	uint16_t absColumnValue = abs(firstPosition.GetColumn() - secondPosition.GetColumn());
	IColumn* firstColumn = m_matrix[firstPosition.GetRow()][firstPosition.GetColumn()];
	IColumn* secondColumn = m_matrix[secondPosition.GetRow()][secondPosition.GetColumn()];
	if (firstColumn->GetPlayer() != secondColumn->GetPlayer())
	{
		return false;
	}
	if (absRowValue == 0 || absColumnValue == 0) 
	{
		return false;
	}
	if (absRowValue + absColumnValue == 3) 
	{
		return true;
	}
	return false;
}

std::string& Board::MakeKey(const Position& firstPosition, const Position& secondPosition)
{
	const auto& raw1 = firstPosition.GetRow(), 
		      & raw2 = secondPosition.GetRow();
	const auto& column1 = firstPosition.GetColumn(), 
			  & column2 = secondPosition.GetColumn();

	std::string key = std::to_string(raw1) + " " + std::to_string(column1) +
		" " + std::to_string(raw2) + " " + std::to_string(column2);
	return key;
}

const std::pair<Position, Position>& Board::ExtractPositionFromKey(std::string key)
{
	std::istringstream in(key);
	uint16_t row, column;
	in >> row >> column;
	Position firstPosition(row, column);

	in >> row >> column;
	Position secondPosition(row, column);

	return std::make_pair(firstPosition, secondPosition);
}


Board::~Board() {
	for (uint16_t index1 = 0; index1 < m_matrix.size(); index1++) {
		for (uint16_t index2 = 0; index2 < m_matrix[index1].size(); index2++) {
			delete m_matrix[index1][index2];
		}
	}
	for (auto bridge : m_bridges)
		delete bridge.second;
}

const IColumn* Board::GetElement(Position position) const
{
	return m_matrix[position.GetRow()][position.GetColumn()];
}

const IColumn* Board::GetElement(uint16_t row, uint16_t column) const
{
	return m_matrix[row][column];
}

const uint16_t Board::GetSize() const
{
	return m_matrix.size();
}

void Board::PlaceColumn(Position& position, IPlayer* player)
{
	if (ValidPlaceColumn(position)) {
		IColumn* newColumn = new Column(player);
		m_matrix[position.GetRow()][position.GetColumn()] = newColumn;
	}
}

void Board::MakeBridge(Position& firstPosition, Position& secondPosition, IPlayer* player)
{
	if (ValidBridge(firstPosition, secondPosition)) {
		Bridge *bridge = new Bridge(m_matrix[firstPosition.GetRow()][firstPosition.GetColumn()],
			m_matrix[secondPosition.GetRow()][secondPosition.GetColumn()]);
		std::string key = MakeKey(firstPosition, secondPosition);
		m_bridges.emplace(key, bridge);
	}
}

void Board::RemoveBridge(Position& firstPosition, Position& secondPosition, IPlayer* player)
{
	
	if (!ValidBridge(firstPosition, secondPosition) || player == nullptr)
	{
		// Handle invalid input, e.g., throw an exception or return an error code.
		return;
	}

	if (std::string key = MakeKey(firstPosition, secondPosition); 
		m_bridges.find(key) != m_bridges.end() &&
		m_bridges[key]->GetFirstColumn()->GetPlayer() == player)
	{
		delete m_bridges[key];
		m_bridges.erase(key);
	}
	
}

const IColumn* Board::operator[](Position pos) const
{
	return GetElement(pos);
}

Board::Board(const Board& otherBoard) 
{
	for (uint16_t line = 0; line < otherBoard.m_matrix.size(); ++line)
		for (uint16_t column = 0; column < otherBoard.m_matrix[line].size(); ++column)
		{
			if (otherBoard.m_matrix[line][column] != nullptr)
				m_matrix[line][column] = new Column(*dynamic_cast<Column*>(otherBoard.m_matrix[line][column]));
			else
				m_matrix[line][column] = nullptr;
		}

	for (auto bridge : otherBoard.m_bridges)
	{
		const auto& [firstPosition,secondPosition] = ExtractPositionFromKey(bridge.first);
		IColumn* firstColumn = nullptr, *secondColumn = nullptr;

		firstColumn = m_matrix[firstPosition.GetRow()][firstPosition.GetColumn()];
		secondColumn = m_matrix[secondPosition.GetRow()][secondPosition.GetColumn()];
		
		Bridge* newBridge = new Bridge(firstColumn, secondColumn);
		m_bridges.emplace(bridge.first,newBridge);
	}

}