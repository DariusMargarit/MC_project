#include "Minimax.h"

Minimax::Minimax(const Board& board, int16_t depth)
	: m_treeHead{ std::make_shared<BoardNode>(board) }
{
	// Empty
}
