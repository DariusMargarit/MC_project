module Board;

import Column;

Board::Board(uint16_t size)
	: m_matrix{size, std::vector<IColumn*>(size, nullptr)}
{

}

bool Board::ValidPlaceColumn(Position position) const
{
	if (m_matrix[position.GetY()][position.GetX()] != nullptr)
	{
		return false;
	}
	return true;
}

bool Board::ValidBridge(Position firstPosition, Position secondPosition) const
{
	int absValueX = abs(firstPosition.GetX() - secondPosition.GetX());
	int absValueY = abs(firstPosition.GetY() - secondPosition.GetY());
	IColumn* firstColumn = m_matrix[firstPosition.GetY()][firstPosition.GetX()];
	IColumn* secondColumn = m_matrix[secondPosition.GetY()][secondPosition.GetX()];
	if (firstColumn->GetPlayer() != secondColumn->GetPlayer())
	{
		return false;
	}
	if (absValueX == 0 || absValueY == 0) 
	{
		return false;
	}
	if (absValueX + absValueY == 3) 
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

IColumn* Board::GetElement(Position position) const
{
	return m_matrix[position.GetY()][position.GetX()];
}

void Board::PlaceColumn(Position& position, IPlayer* player)
{
	if (ValidPlaceColumn(position)) {
		IColumn* newColumn = new Column(player);
		m_matrix[position.GetY()][position.GetX()] = newColumn;
	}
}

void Board::MakeBridge(Position& firstPosition, Position& secondPosition, IPlayer* player)
{
	if (ValidBridge(firstPosition, secondPosition)) {
		Bridge *bridge = new Bridge(m_matrix[firstPosition.GetY()][firstPosition.GetX()],
			m_matrix[secondPosition.GetY()][secondPosition.GetX()]);
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
		return bridge->HasPositions(m_matrix[firstPosition.GetY()][firstPosition.GetX()],
		m_matrix[secondPosition.GetY()][secondPosition.GetX()]) && bridge->GetFirstColumn()->GetPlayer() == player;
		});

	
	if (bridgeIter != m_bridges.end())
	{
		m_bridges.erase(bridgeIter);
		delete* bridgeIter; 
		
	}
	
}

Board::Board(const Board& otherBoard) 
{
	for (size_t i = 0; i < otherBoard.m_matrix.size(); ++i)
		for (size_t j = 0; j < otherBoard.m_matrix[i].size(); ++j)
		{
			if (otherBoard.m_matrix[i][j] != nullptr)
				m_matrix[i][j] = new Column(*dynamic_cast<Column*>(otherBoard.m_matrix[i][j]));
			else
				m_matrix[i][j] = nullptr;
		}

	for (auto bridge : otherBoard.m_bridges)
	{
		IColumn* firstColumn = nullptr, * secondColumn = nullptr, * columnToFind = bridge->GetFirstColumn();
		for (size_t i = 0; i < m_matrix.size() && secondColumn == nullptr; ++i)
			for (size_t j = 0; j < m_matrix[i].size() && secondColumn == nullptr; ++j)
			{
				if (columnToFind == otherBoard.m_matrix[i][j])
				{
					if (firstColumn == nullptr)
					{
						firstColumn = m_matrix[i][j];
						columnToFind = bridge->GetSecondColumn();
					}
					else
					{
						secondColumn = m_matrix[i][j];
						Bridge* newBridge = new Bridge(firstColumn, secondColumn);
						m_bridges.push_back(newBridge);
					}
				}
			}
	}

}