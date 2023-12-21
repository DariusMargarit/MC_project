#pragma once

#include "Board.h"

class BoardNode : public Board
{
public:
	BoardNode(const Board& board);
	BoardNode(const BoardNode& other);
	~BoardNode();

	BoardNode& operator=(const BoardNode& rhs);

private:
	std::vector<BoardNode*> m_children;
};