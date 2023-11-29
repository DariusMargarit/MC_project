
#include <regex>

#include "Board.h"
#include "Column.h"

Board::Board(const uint16_t& size)
	: m_matrix{ size, std::vector<IColumn*>{size, nullptr}}
{
	// Empty
}

bool Board::ValidPlaceColumn(const Position& position) const
{
	if (m_matrix[position.GetRow()][position.GetColumn()] != nullptr)
	{
		return false;
	}
	return true;
}

std::vector<std::vector<IColumn*>> Board::BridgeSurroundingMatrix(const Position& firstPosition, const Position& secondPosition) const
{
	std::vector<std::vector<IColumn*>>surroundingMatrix;
	uint16_t lowerRowIndex = std::min(firstPosition.GetRow(), secondPosition.GetRow());
	uint16_t lowerColumnIndex = std::min(firstPosition.GetColumn(), secondPosition.GetColumn());
	uint16_t absRowValue = abs(firstPosition.GetRow() - secondPosition.GetRow());

	if (lowerRowIndex > 0) --lowerRowIndex;
	if (lowerColumnIndex > 0) --lowerColumnIndex;

	std::vector<IColumn*>row;
	uint16_t higherRowIndex, higherColumnIndex;
	if (absRowValue == 1) 
	{
		higherRowIndex = std::min<uint16_t>(lowerRowIndex + 3, (uint16_t)m_matrix.size() - 1);
		higherColumnIndex = std::min<uint16_t>(lowerColumnIndex + 4, (uint16_t)m_matrix[0].size() - 1);
	} else 
	{
		higherRowIndex = std::min<uint16_t>(lowerRowIndex + 4, (uint16_t)m_matrix.size() - 1);
		higherColumnIndex = std::min<uint16_t>(lowerColumnIndex + 3, (uint16_t)m_matrix[0].size() - 1);
	}
	for (uint16_t rowIndex = lowerRowIndex; rowIndex <= higherRowIndex; ++rowIndex)
	{
		for (uint16_t columnIndex = lowerColumnIndex; columnIndex <= higherColumnIndex; ++columnIndex)
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

bool Board::FindObstacleBridge(Position& bridge1FirstPosition, Position& bridge1SecondPosition) const
{
	std::vector<std::vector<IColumn*>>bridgeSurroundingMatrix = BridgeSurroundingMatrix(bridge1FirstPosition, bridge1SecondPosition);
	std::vector<int16_t> rowDirection = { -2,-1,1,2,2,1,-1,-2 };
	std::vector<int16_t> columnDirection = { 1,2,2,1,-1,-2,-2,-1 };
	for (uint16_t rowIndex = 0; rowIndex < bridgeSurroundingMatrix.size(); ++rowIndex) 
	{
		for (uint16_t columnIndex = 0; columnIndex < bridgeSurroundingMatrix[0].size(); ++columnIndex)
		{
			if (bridgeSurroundingMatrix[rowIndex][columnIndex] != nullptr)
			{
				for (uint8_t directionIndex = 0; directionIndex < rowDirection.size(); ++directionIndex)
				{
					int16_t secondRowIndex = rowIndex + rowDirection[directionIndex];
					int16_t secondColumnIndex = columnIndex + columnDirection[directionIndex];
					if (secondRowIndex < 0 || secondRowIndex > bridgeSurroundingMatrix.size() - 1)
					{
						continue;
					}
					if (secondColumnIndex < 0 || secondColumnIndex > bridgeSurroundingMatrix[0].size() - 1)
					{
						continue;
					}
					if (bridgeSurroundingMatrix[secondRowIndex][secondColumnIndex] != nullptr)
					{
						if (bridgeSurroundingMatrix[secondRowIndex][secondColumnIndex]->GetPlayer() ==
							bridgeSurroundingMatrix[rowIndex][columnIndex]->GetPlayer())
						{
							Position bridge2FirstPosition(rowIndex, columnIndex);
							Position bridge2SecondPosition(secondRowIndex, secondColumnIndex);
							if (bridge2FirstPosition == bridge1FirstPosition || bridge2FirstPosition == bridge1SecondPosition ||
								bridge2SecondPosition == bridge1FirstPosition || bridge2SecondPosition == bridge1SecondPosition)
							{
								continue;
							}
							std::string key1 = MakeKey(bridge2FirstPosition, bridge2SecondPosition);
							std::string key2 = MakeKey(bridge2SecondPosition, bridge2FirstPosition);
							if (m_bridges.find(key1) != m_bridges.end() || m_bridges.find(key2) != m_bridges.end())
							{
								if (doIntersect(bridge1FirstPosition, bridge1SecondPosition,
									bridge2FirstPosition, bridge2SecondPosition))
								{
									return true;
								}
							}
						}
					}
				}
				bridgeSurroundingMatrix[rowIndex][columnIndex] = nullptr;
			}
		}
	}

	return false;
}

bool Board::orientation(Position& A, Position& B, Position& C) const
{
	int16_t val = (B.GetColumn() - A.GetColumn()) * (C.GetRow() - B.GetRow()) -
		(B.GetRow() - A.GetRow()) * (C.GetColumn() - B.GetColumn());

	return (val > 0) ? 0 : 1; // 0 - left, 1 - right
}

bool Board::doIntersect(Position& A1, Position& B1, Position& A2, Position& B2) const
{
	bool o1 = orientation(A1, B1, A2);
	bool o2 = orientation(A1, B1, B2);
	bool o3 = orientation(A2, B2, A1);
	bool o4 = orientation(A2, B2, B1);

	if (o1 != o2 && o3 != o4)
		return true;

	return false;
}

bool Board::ValidBridge(Position& firstPosition, Position& secondPosition) const
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
		if (FindObstacleBridge(firstPosition, secondPosition))
		{
			return false;
		}
		return true;
	}
	return false;
}

const std::string Board::MakeKey(const Position& firstPosition, const Position& secondPosition) const
{
	const auto& raw1 = firstPosition.GetRow(), 
		      & raw2 = secondPosition.GetRow();
	const auto& column1 = firstPosition.GetColumn(), 
			  & column2 = secondPosition.GetColumn();

	std::string key = std::to_string(raw1) + " " + std::to_string(column1) +
		" " + std::to_string(raw2) + " " + std::to_string(column2);
	return key;
}

const std::pair<Position, Position> Board::ExtractPositionFromKey(const std::string& key)
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
	for (auto& bridge : m_bridges)
		delete bridge.second;
}

const IColumn* Board::GetElement(const Position& position) const
{
	return m_matrix[position.GetRow()][position.GetColumn()];
}

const IColumn* Board::GetElement(const uint16_t& row, const uint16_t& column) const
{
	return m_matrix[row][column];
}

const BridgeVector Board::GetBridgesPositions() const
{
	std::regex pattern(R"(\b\d+)");
	BridgeVector bridgesPositions;
	for (auto& bridge : m_bridges)
	{
		std::vector<uint16_t> positions;
		auto string = bridge.first;
		auto it = std::sregex_iterator(string.begin(), string.end(), pattern);
		for (&it; it != std::sregex_iterator(); ++it)
		{
			positions.push_back(std::stoi((*it).str()));
		}
		Position firstColumn(positions[0], positions[1]);
		Position secondColumn(positions[2], positions[3]);
		bridgesPositions.emplace_back(std::move(firstColumn), std::move(secondColumn));
	}
	return std::move(bridgesPositions);
}

const uint16_t Board::GetSize() const
{
	return (uint16_t)m_matrix.size();
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

	for (const auto& bridge : otherBoard.m_bridges)
	{
		const auto& [firstPosition,secondPosition] = ExtractPositionFromKey(bridge.first);
		IColumn* firstColumn = nullptr, *secondColumn = nullptr;

		firstColumn = m_matrix[firstPosition.GetRow()][firstPosition.GetColumn()];
		secondColumn = m_matrix[secondPosition.GetRow()][secondPosition.GetColumn()];
		
		Bridge* newBridge = new Bridge(firstColumn, secondColumn);
		m_bridges.emplace(bridge.first,newBridge);
	}

}