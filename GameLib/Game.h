#pragma once

#include "IGame.h"
#include "Board.h"
#include "Player.h"


class Game : public IGame
{
public:
	Game(const IGameSettings& settings);
	Game(const Game& otherGame);
	Game(Game&& otherGame) noexcept;
	~Game();

	IPlayer* GetTurn() const override;
	IBoard* GetBoard() const override;

	void PlaceColumn(Position position) override;
	void MakeBridge(Position firstPosition, Position secondPosition) override;
	void RemoveBridge(Position firstPosition, Position secondPosition) override;

	Game& operator=(const Game& otherGame);
	Game& operator=(Game&& otherGame) noexcept;
	

private:
	void ChangeTurn();

private:
	Board* m_board;
	uint16_t m_boardSize;
	IPlayer* m_player1, *m_player2, *m_turn;
};


