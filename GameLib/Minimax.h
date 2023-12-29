#pragma once

#include "BoardNode.h"
#include "IGame.h"

class Minimax 
{
public:
	Minimax(Board& board, int16_t depth, IPlayer* firstPlayer, IPlayer* secondPlayer);
	~Minimax() = default;

	std::pair<BridgeVector, Position> GetHint(int16_t depth, IPlayer* player);

private:
	void GenerateTree(Board& board, int16_t depth, std::shared_ptr<BoardNode> currentHead, IPlayer* firstPlayer, IPlayer* secondPlayer);
	bool GameOver() const;
	int16_t Evaluate() const;
	std::shared_ptr<BoardNode> GetBoardNodeHint(int16_t depth, IPlayer* player);
	int16_t minimax(std::shared_ptr<BoardNode> boardNode, int16_t depth, IPlayer* maximizingPlayer,
		int16_t alpha = std::numeric_limits<int16_t>::lowest(),
		int16_t beta = std::numeric_limits<int16_t>::infinity());

private:
	std::shared_ptr<BoardNode> m_treeHead;
	IPlayer* m_firstPlayer;
	IPlayer* m_secondPlayer;
	int16_t m_initialDepth;
};