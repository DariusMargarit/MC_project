#include "Minimax.h"

Minimax::Minimax(Board& board, int16_t depth, IPlayer* firstPlayer, IPlayer* secondPlayer)
	: m_initialDepth{depth}
	, m_firstPlayer{firstPlayer}
	, m_secondPlayer{secondPlayer}
{
	Board newBoard{ board };
	const Position startPositionFirstPlayer(0, newBoard.GetSize() / 2);
	newBoard.PlaceColumn(startPositionFirstPlayer, firstPlayer);
	m_treeHead = std::make_shared<BoardNode>(newBoard, firstPlayer, secondPlayer);
	const Position startPositionSecondPlayer(newBoard.GetSize() / 2, 0);
	newBoard.PlaceColumn(startPositionSecondPlayer, secondPlayer);
	std::shared_ptr<BoardNode> currentHead = std::make_shared<BoardNode>(newBoard, secondPlayer, firstPlayer);
	m_treeHead->InsertChildren(currentHead);
	GenerateTree(newBoard, depth - 2, currentHead, firstPlayer, secondPlayer);
}

std::shared_ptr<BoardNode> Minimax::GetHint(int16_t depth, IPlayer* player)
{
	auto children = m_treeHead->GetChildren();
	int16_t maxEvaluation = -std::numeric_limits<int16_t>::infinity();
	for (auto child : children)
	{
		int16_t evaluation = minimax(child, depth, player);
		if (evaluation > maxEvaluation)
		{
			maxEvaluation = evaluation;
			m_treeHead = child;
		}
	}
	return m_treeHead;
}

void Minimax::GenerateTree(Board& board, int16_t depth, std::shared_ptr<BoardNode> currentHead, IPlayer* firstPlayer, IPlayer* secondPlayer)
{
	if (depth == 0)
	{
		return;
	}
	Board newBoard(board);
	std::stack<Position> positionToStart;
	std::array<int16_t, 8> rowDirection{ { -2,-1,1,2,2,1,-1,-2 } };
	std::array<int16_t, 8> columnDirection{ { 1,2,2,1,-1,-2,-2,-1 } };
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
	while (!positionToStart.empty())
	{
		Position currentPosition = positionToStart.top();
		positionToStart.pop();
		for (uint8_t directionIndex{ 0 }; directionIndex < rowDirection.size(); ++directionIndex)
		{
			Position nextPosition(currentPosition.GetRow() + rowDirection[directionIndex],
				currentPosition.GetColumn() + columnDirection[directionIndex]);
			if (board.ValidPosition(nextPosition.GetRow(), nextPosition.GetColumn()))
			{
				if (board.ValidBridge(currentPosition, nextPosition))
				{
					newBoard.MakeBridge(currentPosition, nextPosition, firstPlayer);
				}
			}
			if (board.ValidPlaceColumn(nextPosition) && board.ValidPosibleBridge(currentPosition, nextPosition))
			{
				newBoard.PlaceColumn(nextPosition, firstPlayer);
				std::shared_ptr<BoardNode> nextHead = std::make_shared<BoardNode>(newBoard, firstPlayer, secondPlayer);
				currentHead->InsertChildren(nextHead);
				GenerateTree(newBoard, depth - 1, nextHead, secondPlayer, firstPlayer);
			}
		}
	}
}

bool Minimax::GameOver() const
{
	if (m_treeHead->GameOver())
	{
		return true;
	}
	return false;
}

int16_t Minimax::Evaluate() const
{
	return m_treeHead->Evaluate();
}

int16_t Minimax::minimax(std::shared_ptr<BoardNode> boardNode, int16_t depth, IPlayer* maximizingPlayer, int16_t alpha, int16_t beta)
{
	return 0;
}
