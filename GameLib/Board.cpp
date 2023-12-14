#include <regex>

#include "Board.h"
#include "Column.h"

Board::Board(const uint16_t& size)
	: m_matrix{ size, std::vector<IColumn*>{size, nullptr}}
	, m_firstPlayerPath {size, std::vector<bool>(size, 0)}
	, m_secondPlayerPath {size, std::vector<bool>(size, 0)}
{
	// Empty
}

bool Board::ValidPosition(const int16_t& row, const int16_t& column) const
{
	if (row < 0 || row >= m_matrix.size() || column < 0 || column >= m_matrix.size())
	{
		return false;
	}
	return true;
}

bool Board::ValidPlaceColumn(const Position& position) const
{
	if (!ValidPosition(position.GetRow(), position.GetColumn()))
	{
		return false;
	}
	if (m_matrix[position.GetRow()][position.GetColumn()] != nullptr)
	{
		return false;
	}

	return true;
}

bool Board::FindObstacleBridge(Position& bridge1FirstPosition, Position& bridge1SecondPosition) const
{
	uint16_t lowerRowIndex{ std::min(bridge1FirstPosition.GetRow(), bridge1SecondPosition.GetRow()) };
	uint16_t lowerColumnIndex{ std::min(bridge1FirstPosition.GetColumn(), bridge1SecondPosition.GetColumn()) };
	uint16_t absRowValue = abs(bridge1FirstPosition.GetRow() - bridge1SecondPosition.GetRow()) ;
	std::vector<int16_t> rowDirection{ { -2,-1,1,2,2,1,-1,-2 } };
	std::vector<int16_t> columnDirection{ { 1,2,2,1,-1,-2,-2,-1 } };
	uint8_t rowAddition, columnAddition;
	if (absRowValue == 1)
	{
		rowAddition = 1, columnAddition = 2;
	}
	else
	{
		rowAddition = 2, columnAddition = 1;
	}
	for (uint16_t rowIndex{ lowerRowIndex }; rowIndex <= lowerRowIndex + rowAddition; ++rowIndex)
	{
		for (uint16_t columnIndex{ lowerColumnIndex }; columnIndex <= lowerColumnIndex + columnAddition; ++columnIndex)
		{
			if (m_matrix[rowIndex][columnIndex] != nullptr)
			{
				for (uint8_t directionIndex{ 0 }; directionIndex < rowDirection.size(); ++directionIndex)
				{
					int16_t secondRowIndex{ rowIndex + rowDirection[directionIndex] };
					int16_t secondColumnIndex{ columnIndex + columnDirection[directionIndex] };
					if (!ValidPosition(secondRowIndex, secondColumnIndex))
					{
						continue;
					}
					if (m_matrix[secondRowIndex][secondColumnIndex] != nullptr)
					{
						if (m_matrix[secondRowIndex][secondColumnIndex]->GetPlayer() ==
							m_matrix[rowIndex][columnIndex]->GetPlayer())
						{
							Position bridge2FirstPosition(rowIndex, columnIndex);
							Position bridge2SecondPosition(secondRowIndex, secondColumnIndex);
							IColumn* bridge1FirstColumn{ m_matrix[bridge1FirstPosition.GetRow()][bridge1FirstPosition.GetColumn()] };
							IColumn* bridge1SecondColumn{ m_matrix[bridge1SecondPosition.GetRow()][bridge1SecondPosition.GetColumn()] };
							IColumn* bridge2FirstColumn{ m_matrix[rowIndex][columnIndex] };
							IColumn* bridge2SecondColumn{ m_matrix[secondRowIndex][secondColumnIndex] };
							if (bridge1FirstColumn == bridge2FirstColumn || bridge1FirstColumn == bridge2SecondColumn ||
								bridge1SecondColumn == bridge2FirstColumn || bridge1SecondColumn == bridge2SecondColumn)
							{
								continue;
							}
							
							if (BridgeExists(bridge2FirstPosition, bridge2SecondPosition))
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
			}
		}
	}

	return false;
}

bool Board::Orientation(Position& A, Position& B, Position& C) const
{
	int16_t val{ (B.GetColumn() - A.GetColumn()) * (C.GetRow() - B.GetRow()) -
		(B.GetRow() - A.GetRow()) * (C.GetColumn() - B.GetColumn()) };

	return (val > 0) ? 0 : 1; // 0 - left, 1 - right
}

bool Board::doIntersect(Position& A1, Position& B1, Position& A2, Position& B2) const
{
	bool o1{ Orientation(A1, B1, A2) };
	bool o2{ Orientation(A1, B1, B2) };
	bool o3{ Orientation(A2, B2, A1) };
	bool o4{ Orientation(A2, B2, B1) };

	if (o1 != o2 && o3 != o4)
		return true;

	return false;
}

bool Board::ValidBridge(Position& firstPosition, Position& secondPosition) const
{
	if (BridgeExists(firstPosition, secondPosition)) return false;

	uint16_t absRowValue = abs(firstPosition.GetRow() - secondPosition.GetRow()) ;
	uint16_t absColumnValue = abs(firstPosition.GetColumn() - secondPosition.GetColumn()) ;
	IColumn* firstColumn{ m_matrix[firstPosition.GetRow()][firstPosition.GetColumn()] };
	IColumn* secondColumn{ m_matrix[secondPosition.GetRow()][secondPosition.GetColumn()] };
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
	const auto& row1{ firstPosition.GetRow() },
		      & row2{ secondPosition.GetRow() };
	const auto& column1{ firstPosition.GetColumn() },
		      & column2{ secondPosition.GetColumn() };

	std::string key{ std::to_string(row1) + " " + std::to_string(column1) +
		" " + std::to_string(row2) + " " + std::to_string(column2) };
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

void Board::MarkPathWithOnes(Position& startPosition, std::vector<std::vector<bool>>* playerPath)
{
	std::vector<int16_t> rowDirection{ { -2,-1,1,2,2,1,-1,-2 } };
	std::vector<int16_t> columnDirection{ { 1,2,2,1,-1,-2,-2,-1 } };
	std::stack<Position> positionStack;
	positionStack.push(startPosition);
	while (!positionStack.empty())
	{
		Position currentPosition = positionStack.top();
		positionStack.pop();
		bool modifiedMatrix = false;
		for (uint8_t directionIndex{ 0 }; directionIndex < rowDirection.size(); ++directionIndex)
		{
			int16_t nextPositionRow = currentPosition.GetRow() + rowDirection[directionIndex];
			int16_t nextPositionColumn = currentPosition.GetColumn() + columnDirection[directionIndex];
			if (ValidPosition(nextPositionRow, nextPositionColumn))
			{
				Position nextPosition(nextPositionRow, nextPositionColumn);
				if (BridgeExists(currentPosition, nextPosition))
				{
					if ((*playerPath)[nextPositionRow][nextPositionColumn] == 1)
					{
						(*playerPath)[currentPosition.GetRow()][currentPosition.GetColumn()] = 1;
						modifiedMatrix = true;
						continue;
					}
					positionStack.push(nextPosition);
				}
			}
		}
		if (!modifiedMatrix)
		{
			break;
		}
	}
}

void Board::ComputePathToWin(bool player, bool action, Position& firstPosition, Position& secondPosition)
{
	std::vector<std::vector<bool>>* playerPath{ nullptr };
	if (player == 0)
	{
		playerPath = &m_firstPlayerPath;
	}
	else
	{
		playerPath = &m_secondPlayerPath;
	}
	if (action == 0)
	{
		if (firstPosition.GetRow() == 0 || firstPosition.GetColumn() == 0)
		{
			(*playerPath)[firstPosition.GetRow()][firstPosition.GetColumn()] = 1;
		}
		else if (secondPosition.GetRow() == 0 || secondPosition.GetColumn() == 0)
		{
			(*playerPath)[secondPosition.GetRow()][secondPosition.GetColumn()] = 1;
		}

		if ((*playerPath)[firstPosition.GetRow()][firstPosition.GetColumn()] == 0)
		{
			MarkPathWithOnes(firstPosition, playerPath);
		}
		if ((*playerPath)[secondPosition.GetRow()][secondPosition.GetColumn()] == 0)
		{
			MarkPathWithOnes(secondPosition, playerPath);
		}
	}
	else
	{
		return;
	}
}

bool Board::CheckWinner(bool player)
{
	if (player == 0)
	{
		for (uint16_t columnIndex{ 0 }; columnIndex < m_matrix.size(); ++columnIndex)
		{
			if (m_firstPlayerPath[m_matrix.size() - 1][columnIndex] == 1)
			{
				return true;
			}
		}
	}
	else
	{
		for (uint16_t rowIndex{ 0 }; rowIndex < m_matrix.size(); ++rowIndex)
		{
			if (m_firstPlayerPath[rowIndex][m_matrix.size() - 1] == 1)
			{
				return true;
			}
		}
	}
	return false;
}


Board::~Board() {
	for (uint16_t index1{ 0 }; index1 < m_matrix.size(); index1++) {
		for (uint16_t index2{ 0 }; index2 < m_matrix[index1].size(); index2++) {
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
	std::regex pattern{R"(\b\d+)"};
	BridgeVector bridgesPositions;
	for (auto& bridge : m_bridges)
	{
		std::vector<uint16_t> positions;
		auto string{ bridge.first };
		auto it{ std::sregex_iterator(string.begin(), string.end(), pattern) };
		for (&it; it != std::sregex_iterator(); ++it)
		{
			positions.push_back(std::stoi((*it).str()));
		}
		Position firstColumn{positions[0], positions[1]};
		Position secondColumn{positions[2], positions[3]};
		bridgesPositions.emplace_back(std::move(firstColumn), std::move(secondColumn));
	}
	return std::move(bridgesPositions);
}

const uint16_t Board::GetSize() const
{
	return (uint16_t)m_matrix.size();
}

bool Board::PlaceColumn(Position& position, IPlayer* player)
{
	if (ValidPlaceColumn(position)) {
		IColumn* newColumn{ new Column(player) };
		m_matrix[position.GetRow()][position.GetColumn()] = newColumn ;

		return true;
	}
	return false;
}

bool Board::MakeBridge(Position& firstPosition, Position& secondPosition, IPlayer* player)
{
	if (ValidBridge(firstPosition, secondPosition)) {
		Bridge* bridge{ new Bridge(m_matrix[firstPosition.GetRow()][firstPosition.GetColumn()],
			m_matrix[secondPosition.GetRow()][secondPosition.GetColumn()]) };
		std::string key{ MakeKey(firstPosition, secondPosition) };
		m_bridges.emplace(key, bridge);

		return true;
	}
	return false;
}

bool Board::RemoveBridge(Position& firstPosition, Position& secondPosition, IPlayer* player)
{
	if (!BridgeExists(firstPosition, secondPosition)) 
		return false;

	const auto firstKey{ MakeKey(firstPosition, secondPosition) };
	const auto secondKey{ MakeKey(secondPosition, firstPosition) };
	if (m_bridges.find(firstKey) != m_bridges.end())
	{
		delete m_bridges[firstKey];
		m_bridges.erase(firstKey);
	}
	else
	{
		delete m_bridges[secondKey];
		m_bridges.erase(secondKey);
	}
	return true;
}

bool Board::BridgeExists(const Position& firstPosition, const Position& secondPosition) const
{
	const auto firstKey{ MakeKey(firstPosition, secondPosition) };
	const auto secondKey{ MakeKey(secondPosition, firstPosition) };
	if (m_bridges.find(firstKey)  != m_bridges.end() ||
		m_bridges.find(secondKey) != m_bridges.end()) return true;
	return false;
}

const IColumn* Board::operator[](Position pos) const
{
	return GetElement(pos);
}

Board::Board(const Board& otherBoard) 
{
	for (uint16_t line{ 0 }; line < otherBoard.m_matrix.size(); ++line)
		for (uint16_t column{ 0 }; column < otherBoard.m_matrix[line].size(); ++column)
		{
			if (otherBoard.m_matrix[line][column] != nullptr)
				m_matrix[line][column] = new Column(*dynamic_cast<Column*>(otherBoard.m_matrix[line][column])) ;
			else
				m_matrix[line][column] = nullptr ;
		}

	for (const auto& bridge : otherBoard.m_bridges)
	{
		const auto& [firstPosition, secondPosition] { ExtractPositionFromKey(bridge.first)};
		IColumn* firstColumn{ nullptr }, * secondColumn{ nullptr };

		firstColumn = m_matrix[firstPosition.GetRow()][firstPosition.GetColumn()] ;
		secondColumn = m_matrix[secondPosition.GetRow()][secondPosition.GetColumn()] ;
		
		Bridge* newBridge{ new Bridge(firstColumn, secondColumn) };
		m_bridges.emplace(bridge.first,newBridge);
	}

}