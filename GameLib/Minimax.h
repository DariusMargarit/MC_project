#pragma once

#include "BoardNode.h"
#include "IGame.h"

class Minimax 
{
public:
	Minimax(const Board& board);
	~Minimax();

private:
	bool GameOver() const;
	int16_t Evaluate() const;

private:
	std::unique_ptr<Board> m_board;
	std::unique_ptr<BoardNode> m_treeHead;
};