#pragma once

#include <memory>
#include <random>

#include "MinedColumn.h"
#include "Board.h"

class MinedGame
{
public:
	MinedGame(BoardPtr board);
	MinedGame(const MinedGame& rhs) = default;
	MinedGame(MinedGame&& rhs) = default;
	~MinedGame() = default;
	MinedGame& operator=(const MinedGame& rhs) = default;
	MinedGame& operator=(MinedGame&& rhs) noexcept = default;

	void DestroyArea(const Position& position, Player* firstPlayer, Player* secondPlayer);
	void AddMines();

private:
	void PlaceMine(const Position& position);
	BoardPtr m_board;
};