#include <regex>
#include <random>

#include "Board.h"
#include "Column.h"
#include "MinedColumn.h"

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

bool Board::FindObstacleBridge(Position& firstPos, Position& secondPos) const
{
	uint16_t lowerRowIndex{ std::min(firstPos.GetRow(), secondPos.GetRow()) };
	uint16_t lowerColumnIndex{ std::min(firstPos.GetColumn(), secondPos.GetColumn()) };
	uint16_t absRowValue = abs(firstPos.GetRow() - secondPos.GetRow()) ;
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
							IColumn* bridge1FirstColumn{ m_matrix[firstPos.GetRow()][firstPos.GetColumn()] };
							IColumn* bridge1SecondColumn{ m_matrix[secondPos.GetRow()][secondPos.GetColumn()] };
							IColumn* bridge2FirstColumn{ m_matrix[rowIndex][columnIndex] };
							IColumn* bridge2SecondColumn{ m_matrix[secondRowIndex][secondColumnIndex] };
							if (bridge1FirstColumn == bridge2FirstColumn || bridge1FirstColumn == bridge2SecondColumn ||
								bridge1SecondColumn == bridge2FirstColumn || bridge1SecondColumn == bridge2SecondColumn)
							{
								continue;
							}
							
							if (BridgeExists(bridge2FirstPosition, bridge2SecondPosition))
							{
								if (doIntersect(firstPos, secondPos,
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

bool Board::ValidBridge(Position& firstPos, Position& secondPos) const
{
	if (BridgeExists(firstPos, secondPos)) return false;

	uint16_t absRowValue = abs(firstPos.GetRow() - secondPos.GetRow()) ;
	uint16_t absColumnValue = abs(firstPos.GetColumn() - secondPos.GetColumn()) ;
	IColumn* firstColumn{ m_matrix[firstPos.GetRow()][firstPos.GetColumn()] };
	IColumn* secondColumn{ m_matrix[secondPos.GetRow()][secondPos.GetColumn()] };
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
		if (FindObstacleBridge(firstPos, secondPos))
		{
			return false;
		}
		return true;
	}
	return false;
}

const std::string Board::MakeKey(const Position& firstPos, const Position& secondPos) const
{
	const auto& row1{ firstPos.GetRow() },
		      & row2{ secondPos.GetRow() };
	const auto& column1{ firstPos.GetColumn() },
		      & column2{ secondPos.GetColumn() };

	std::string key{ std::to_string(row1) + " " + std::to_string(column1) +
		" " + std::to_string(row2) + " " + std::to_string(column2) };
	return std::move(key);
}

const std::pair<Position, Position> Board::ExtractPositionFromKey(const std::string& key)
{
	std::istringstream in(key);
	uint16_t row, column;
	in >> row >> column;
	Position firstPosition(row, column);

	in >> row >> column;
	Position secondPosition(row, column);

	return std::move(std::make_pair(firstPosition, secondPosition));
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

void Board::ComputePathToWin(bool player, bool action, Position& firstPos, Position& secondPos)
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
		if (firstPos.GetRow() == 0 || firstPos.GetColumn() == 0)
		{
			(*playerPath)[firstPos.GetRow()][firstPos.GetColumn()] = 1;
		}
		else if (secondPos.GetRow() == 0 || secondPos.GetColumn() == 0)
		{
			(*playerPath)[secondPos.GetRow()][secondPos.GetColumn()] = 1;
		}

		if ((*playerPath)[firstPos.GetRow()][firstPos.GetColumn()] == 0)
		{
			MarkPathWithOnes(firstPos, playerPath);
		}
		if ((*playerPath)[secondPos.GetRow()][secondPos.GetColumn()] == 0)
		{
			MarkPathWithOnes(secondPos, playerPath);
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

void Board::AddMines()
{
	uint16_t numberMines{ (uint16_t)((5 / 100) * (GetSize() * GetSize())) };
	while(numberMines)
	{
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> distr(1, GetSize() - 2);

		uint16_t raw{ (uint16_t)distr(eng) }, column{ (uint16_t)distr(eng) };
		Position pos{ raw,column };

		PlaceMine(pos);
		--numberMines;
	}
}

Board::~Board() {
	for (uint16_t index1{ 0 }; index1 < m_matrix.size(); ++index1) {
		for (uint16_t index2{ 0 }; index2 < m_matrix[index1].size(); ++index2) {
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
		Position secondColumn{ positions[2], positions[3] };
		bridgesPositions.emplace_back(std::move(firstColumn), std::move(secondColumn));
	}
	return std::move(bridgesPositions);
}

const uint16_t Board::GetSize() const
{
	return std::move((uint16_t)m_matrix.size());
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

void Board::PlaceMine(Position& position)
{
	IColumn* newColumn{ new MinedColumn };
	m_matrix[position.GetRow()][position.GetColumn()] = newColumn;

}

bool Board::MakeBridge(Position& firstPos, Position& secondPos, IPlayer* player)
{
	if (ValidBridge(firstPos, secondPos)) {
		Bridge* bridge{ new Bridge(m_matrix[firstPos.GetRow()][firstPos.GetColumn()],
			m_matrix[secondPos.GetRow()][secondPos.GetColumn()]) };
		std::string key{ MakeKey(firstPos, secondPos) };
		m_bridges.emplace(key, bridge);

		return true;
	}
	return false;
}

bool Board::RemoveBridge(Position& firstPos, Position& secondPos, IPlayer* player)
{
	if (!BridgeExists(firstPos, secondPos)) 
		return false;

	const auto firstKey{ MakeKey(firstPos, secondPos) };
	const auto secondKey{ MakeKey(secondPos, firstPos) };
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

bool Board::BridgeExists(const Position& firstPos, const Position& secondPos) const
{
	const auto firstKey{ MakeKey(firstPos, secondPos) };
	const auto secondKey{ MakeKey(secondPos, firstPos) };
	if (m_bridges.find(firstKey)  != m_bridges.end() ||
		m_bridges.find(secondKey) != m_bridges.end()) return true;
	return false;
}

const IColumn* Board::operator[](Position pos) const
{
	return GetElement(pos);
}

Board::Board(const Board & other) 
	: m_matrix(other.GetSize(), std::vector<IColumn*>(other.GetSize(), nullptr))
{
	for (uint16_t line{ 0 }; line < m_matrix.size(); ++line)
	{
		for (uint16_t column{ 0 }; column < m_matrix[line].size(); ++column)
		{
			if (!other.m_matrix[line][column]) continue;
			
			const auto basicColumn = dynamic_cast<Column*>(other.m_matrix[line][column]);
			if (basicColumn) m_matrix[line][column] = new Column(*basicColumn);
			const auto minedColumn = dynamic_cast<MinedColumn*>(other.m_matrix[line][column]);
			if (minedColumn) m_matrix[line][column] = new MinedColumn(*minedColumn);
		}
	}

	for (const auto& bridge : other.m_bridges)
	{
		const auto& [firstPosition, secondPosition] { ExtractPositionFromKey(bridge.first)};
		IColumn* firstColumn{ nullptr }, * secondColumn{ nullptr };

		firstColumn = m_matrix[firstPosition.GetRow()][firstPosition.GetColumn()] ;
		secondColumn = m_matrix[secondPosition.GetRow()][secondPosition.GetColumn()] ;
		
		Bridge* newBridge{ new Bridge(firstColumn, secondColumn) };
		m_bridges.emplace(bridge.first,newBridge);
	}

}