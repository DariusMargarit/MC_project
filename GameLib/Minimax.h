#pragma once

#include "BoardNode.h"
#include "IGame.h"

class Minimax 
{
public:
	Minimax(const Board& board, int16_t depth);
	~Minimax() = default;

	

private:
	bool GameOver() const;
	int16_t Evaluate() const;

private:
	std::shared_ptr<BoardNode> m_treeHead;
};