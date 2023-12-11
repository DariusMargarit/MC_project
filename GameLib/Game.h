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
	~Game() = default;

	IPlayer* GetTurn() const override;
	IBoard* GetBoard() const override;
	IPlayer* CheckWinner() const override;

	IPlayer* GetFirstPlayer() const override;
	IPlayer* GetSecondPlayer() const override;

	void PlaceColumn(Position position) override;
	void MakeBridge(Position firstPosition, Position secondPosition) override;
	void RemoveBridge(Position firstPosition, Position secondPosition) override;
	void SwapPlayers();

	Game& operator=(const Game& otherGame);
	Game& operator=(Game&& otherGame) noexcept;

private:
	void AddObserver(ObserverPtr observer) override;
	void RemoveObserver(ObserverPtr observer) override;
	void NotifyPlaceColumn(Position position, IPlayer* player) const;
	void NotifyMakeBridge(Position firstPosition, Position secondPosition, IPlayer* player) const;
	void NotifyRemoveBridge(Position firstPosition, Position secondPosition, IPlayer* player) const;

	void ChangeTurn();
	void ComputePathToWin(bool action, Position& firstPosition, Position& secondPosition) const; // action = 0 - make, 1 - remove

private:
	Board* m_board;
	uint16_t m_boardSize;
	IPlayer* m_player1, *m_player2, *m_turn;
	ObserverList m_observers;
};


