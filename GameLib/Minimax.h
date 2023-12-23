#pragma once

#include "BoardNode.h"
#include "IGame.h"

class Minimax 
{
public:
	Minimax(Board& board, int16_t depth, IPlayer* firstPlayer, IPlayer* secondPlayer);
	~Minimax() = default;

private:
	void GenerateTree(Board& board, int16_t depth, std::shared_ptr<BoardNode> currentHead, IPlayer* firstPlayer, IPlayer* secondPlayer);
	bool GameOver() const;
	int16_t Evaluate() const;

private:
	std::shared_ptr<BoardNode> m_treeHead;
	IPlayer* m_firstPlayer;
	IPlayer* m_secondPlayer;
	int16_t m_initialDepth;
};