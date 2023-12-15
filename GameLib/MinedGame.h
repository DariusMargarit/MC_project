#pragma once
#include "IGame.h"
#include "Board.h"
#include "Player.h"
#include <random>
class MinedGame : public IGame
{
public:
	MinedGame(const IGameSettings& settings);
	MinedGame(const MinedGame& rhs);
	MinedGame(MinedGame&& rhs) = default;
	~MinedGame();
	MinedGame& operator=(const MinedGame& rhs);
	MinedGame& operator=(MinedGame&& rhs) noexcept = default;

private:
	Board* m_board;
	uint16_t m_boardSize;
	IPlayer* m_player1, * m_player2, * m_turn;
	ObserverList m_observers;
};