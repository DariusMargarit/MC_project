#pragma once

#include "Board.h"
#include <memory>

class BoardNode : public Board
{
public:
	BoardNode(const Board& board);
	BoardNode(const BoardNode& other);
	~BoardNode() = default;

	BoardNode& operator=(const BoardNode& rhs);

private:
	std::vector<std::unique_ptr<BoardNode>> m_children;
};