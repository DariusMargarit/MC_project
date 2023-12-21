#include "Minimax.h"

Minimax::Minimax(const Board& board)
	: m_board{std::make_unique<Board>(board)}
{
	// Empty
}
