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

bool Board::ValidBridge(Position firstPosition, Position secondPosition) const
{
	int absValueRow = abs(firstPosition.GetRow() - secondPosition.GetRow());
	int absValueColumn = abs(firstPosition.GetColumn() - secondPosition.GetColumn());
	IColumn* firstColumn = m_matrix[firstPosition.GetRow()][firstPosition.GetColumn()];
	IColumn* secondColumn = m_matrix[secondPosition.GetRow()][secondPosition.GetColumn()];
	if (firstColumn->GetPlayer() != secondColumn->GetPlayer())
	{
		return false;
	}
	if (absValueRow == 0 || absValueColumn == 0) 
	{
		return false;
	}
	if (absValueRow + absValueColumn == 3) 
	{
		return true;
	}
	return false;
}


Board::~Board() {
	for (int index1 = 0; index1 < m_matrix.size(); index1++) {
		for (int index2 = 0; index2 < m_matrix[index1].size(); index2++) {
			delete m_matrix[index1][index2];
		}
	}
	for (auto bridge : m_bridges)
		delete bridge;
}

const IColumn* Board::GetElement(Position position) const
{
	return m_matrix[position.GetRow()][position.GetColumn()];
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
		m_bridges.push_back(bridge);
	}
}



void Board::RemoveBridge(Position& firstPosition, Position& secondPosition, IPlayer* player)
{
	
	if (!ValidBridge(firstPosition, secondPosition) || player == nullptr)
	{
		// Handle invalid input, e.g., throw an exception or return an error code.
		return;
	}

	
	auto bridgeIter = std::find_if(m_bridges.begin(), m_bridges.end(), [&](const Bridge* bridge) {
		return bridge->HasPositions(m_matrix[firstPosition.GetColumn()][firstPosition.GetRow()],
		m_matrix[secondPosition.GetColumn()][secondPosition.GetRow()]) && bridge->GetFirstColumn()->GetPlayer() == player;
		});

	
	if (bridgeIter != m_bridges.end())
	{
		m_bridges.erase(bridgeIter);
		delete* bridgeIter; 
		
	}
	
}

const IColumn* Board::operator[](Position pos) const
{
	return GetElement(pos);
}

Board::Board(const Board& otherBoard) 
{
	for (size_t line = 0; line < otherBoard.m_matrix.size(); ++line)
		for (size_t column = 0; column < otherBoard.m_matrix[line].size(); ++column)
		{
			if (otherBoard.m_matrix[line][column] != nullptr)
				m_matrix[line][column] = new Column(*dynamic_cast<Column*>(otherBoard.m_matrix[line][column]));
			else
				m_matrix[line][column] = nullptr;
		}

	for (auto bridge : otherBoard.m_bridges)
	{
		IColumn* firstColumn = nullptr, * secondColumn = nullptr, * columnToFind = bridge->GetFirstColumn();
		for (size_t line = 0; line < m_matrix.size() && secondColumn == nullptr; ++line)
			for (size_t column = 0; column < m_matrix[line].size() && secondColumn == nullptr; ++column)
			{
				if (columnToFind == otherBoard.m_matrix[line][column])
				{
					if (firstColumn == nullptr)
					{
						firstColumn = m_matrix[line][column];
						columnToFind = bridge->GetSecondColumn();
					}
					else
					{
						secondColumn = m_matrix[line][column];
						Bridge* newBridge = new Bridge(firstColumn, secondColumn);
						m_bridges.push_back(newBridge);
					}
				}
			}
	}

}