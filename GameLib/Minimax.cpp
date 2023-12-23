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
}

bool Minimax::GameOver() const
{
	return false;
}

int16_t Minimax::Evaluate() const
{
	return 0;
}
