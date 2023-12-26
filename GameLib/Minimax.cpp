#include "Minimax.h"

Minimax::Minimax(Board& board, int16_t depth, IPlayer* firstPlayer, IPlayer* secondPlayer)
	: m_initialDepth{depth}
	, m_firstPlayer{firstPlayer}
	, m_secondPlayer{secondPlayer}
{
	const Position startPositionFirstPlayer(0, board.GetSize() / 2);
	board.PlaceColumn(startPositionFirstPlayer, firstPlayer);
	m_treeHead = std::make_shared<BoardNode>(board, firstPlayer, secondPlayer);
	const Position startPositionSecondPlayer(board.GetSize() / 2, 0);
	board.PlaceColumn(startPositionSecondPlayer, secondPlayer);
	std::shared_ptr<BoardNode> currentHead = std::make_shared<BoardNode>(board, secondPlayer, firstPlayer);
	m_treeHead->InsertChildren(currentHead);
	GenerateTree(board, depth - 2, currentHead, firstPlayer, secondPlayer);
}

void Minimax::GenerateTree(Board& board, int16_t depth, std::shared_ptr<BoardNode> currentHead, IPlayer* firstPlayer, IPlayer* secondPlayer)
{
	if (depth == 0)
	{
		return;
	}
	Board newBoard(board);
	std::stack<Position> positionToStart;
	for (uint16_t line{ 0 }; line < board.GetSize(); ++line)
	{
		for (uint16_t column{ 0 }; column < board.GetSize(); ++column)
		{
			Position position(line, column);
			if (board.GetElement(position) != nullptr)
			{
				if (board.GetElement(position)->GetPlayer() == firstPlayer)
				{
					positionToStart.push(position);
				}
			}
		}
	}
	std::array<int16_t, 8> rowDirection{ { -2,-1,1,2,2,1,-1,-2 } };
	std::array<int16_t, 8> columnDirection{ { 1,2,2,1,-1,-2,-2,-1 } };
	while (!positionToStart.empty())
	{
		Position currentPosition = positionToStart.top();
		positionToStart.pop();
		for (uint8_t directionIndex{ 0 }; directionIndex < rowDirection.size(); ++directionIndex)
		{
			Position nextPosition(currentPosition.GetRow() + rowDirection[directionIndex],
				currentPosition.GetColumn() + columnDirection[directionIndex]);
			if (board.ValidPlaceColumn(nextPosition) && board.ValidPosibleBridge(currentPosition, nextPosition))
			{
				newBoard.PlaceColumn(nextPosition, firstPlayer);
				newBoard.MakeBridge(currentPosition, nextPosition, firstPlayer);
				std::shared_ptr<BoardNode> nextHead = std::make_shared<BoardNode>(newBoard, firstPlayer, secondPlayer);
				currentHead->InsertChildren(nextHead);
				GenerateTree(newBoard, depth - 1, nextHead, secondPlayer, firstPlayer);
			}
		}
	}
}

bool Minimax::GameOver() const
{
	return false;
}

int16_t Minimax::Evaluate() const
{
	return 0;
}
