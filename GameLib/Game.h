#pragma once

#include "IGame.h"
#include "Board.h"
#include "Player.h"

#include "../TwixtTextParser/ITwixtParser.h"

class Game : public IGame
{
public:
	Game(const IGameSettings& settings);
	Game(const Game& rhs);
	Game(Game&& rhs) noexcept;
	~Game() = default;

	IPlayer* GetTurn() const override;
	IBoard* GetBoard() const override;
	IPlayer* CheckWinner() const override;

	IPlayer* GetFirstPlayer() const override;
	IPlayer* GetSecondPlayer() const override;

	void PlaceColumn(Position position) override;
	void MakeBridge(Position firstPos, Position secondPos) override;
	void RemoveBridge(Position firstPos, Position secondPos) override;
	void SwapPlayers();

	Game& operator=(const Game& rhs);
	Game& operator=(Game&& rhs) noexcept;

private:
	void AddObserver(ObserverPtr observer) override;
	void RemoveObserver(ObserverPtr observer) override;
	void NotifyPlaceColumn(Position position, IPlayer* player) const;
	void NotifyMakeBridge(Position lhs, Position rhs, IPlayer* player) const;
	void NotifyRemoveBridge(Position lhs, Position rhs, IPlayer* player) const;

	void ChangeTurn();
	void ComputePathToWin(bool action, Position& lhs, Position& rhs) const; // action = 0 - make, 1 - remove

private:
	Board* m_board;
	uint16_t m_boardSize;
	IPlayer* m_player1, *m_player2, *m_turn;
	parser::TwixtParserPtr m_parser;

	ObserverList m_observers;
};


