#pragma once

#include <optional>

#include "IGame.h"
#include "Board.h"
#include "Player.h"
#include "Minimax.h"
#include "MinedGame.h"

#include "../TwixtTextParser/ITwixtParser.h"

class Game : public IGame
{
public:
	Game(const IGameSettings& settings);
	Game(const Game & other);
	Game(Game && other) noexcept;
	~Game() = default;

	IPlayer* GetTurn() const override;
	IBoardPtr GetBoard() const override;
	IPlayer* CheckWinner() const override;

	IPlayer* GetFirstPlayer() const override;
	IPlayer* GetSecondPlayer() const override;

	void PreviewTable(int historyIndex) override;
	bool PlaceColumn(Position position) override;
	bool MakeBridge(Position firstPos, Position secondPos) override;
	bool RemoveBridge(Position firstPos, Position secondPos) override;

	void SwapResponse(bool response) override;
	void SwapPlayers();

	void AddObserver(ObserverPtr observer) override;
	void RemoveObserver(ObserverPtr observer) override;

	bool SaveGame(const std::string_view path, StorageFormat format) override;
	bool LoadGame(const std::string_view path, StorageFormat format) override;

	std::pair<BridgeVector, Position> GetHint(int16_t depth, IPlayer* player) const;

	Game& operator=(const Game& rhs);
	Game& operator=(Game&& rhs) noexcept;

private:
	void NotifyPlaceColumn(Position position, IPlayer* player) const;
	void NotifyMakeBridge(Position firstPos, Position secondPos, IPlayer* player) const;
	void NotifyRemoveBridge(Position firstPos, Position secondPos, IPlayer* player) const;
	void NotifySwapEvent() const;
	void NotifySwapResponse(bool response) const;
	void NotifyGameEnd(EGameResult result) const;

	void ChangeTurn();
	void ComputePathToWin(bool action, Position& firstPos, Position& secondPos) const; // action = 0 - make, 1 - remove
	parser::STNGameRepresentation GetSTNGameRepresentation() const;
	Board STNGameRepresentationToBoard(const parser::STNGameRepresentation& game) const;

private:
	BoardPtr m_board;
	uint16_t m_boardSize;
	Player* m_player1, * m_player2;
	IPlayer* m_turn;
	Minimax* m_minimax;
	MinedGame* m_minedGame;
	EGamemode m_gamemode;
	parser::TwixtParserPtr m_parser;

	bool m_notificationsDisabled, m_firstGameMove;

	ObserverList m_observers;

};


