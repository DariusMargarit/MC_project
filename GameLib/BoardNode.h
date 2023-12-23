#pragma once
#include <memory>

#include "Board.h"
#include "IPlayer.h"

class BoardNode : public Board
{
public:
	BoardNode(const Board& board, IPlayer* maximizingPlayer, IPlayer* minimizingPlayer);
	BoardNode(const BoardNode& other);
	~BoardNode() = default;

	void InsertChildren(std::shared_ptr<BoardNode> children);
	bool GameOver() const;
	int16_t Evaluate() const;

	BoardNode& operator=(const BoardNode& rhs);

private:
	std::vector<std::shared_ptr<BoardNode>> m_children;
	IPlayer* m_maximizingPlayer;
	IPlayer* m_minimizingPlayer;
};