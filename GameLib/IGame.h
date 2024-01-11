#pragma once

#include "IGameSettings.h"
#include "IGameObserver.h"
#include "Position.h"
#include "IPlayer.h"
#include "IBoard.h"

using IGamePtr = std::shared_ptr<struct IGame>;

enum class StorageFormat
{
	STN,  // standard twixt notation
	PTG,  // portable twixt game
};

struct IGame
{
	static IGamePtr Produce(const IGameSettings& settings);

	virtual void AddObserver(ObserverPtr observer) = 0;
	virtual void RemoveObserver(ObserverPtr observer) = 0;

	virtual IPlayer* GetTurn() const = 0;
	virtual IBoardPtr GetBoard() const = 0;
	virtual IPlayer* CheckWinner() const = 0;

	virtual IPlayer* GetFirstPlayer() const = 0;
	virtual IPlayer* GetSecondPlayer() const = 0;

	virtual bool PlaceColumn(Position position) = 0;
	virtual bool MakeBridge(Position firstPos, Position secondPos) = 0;
	virtual bool RemoveBridge(Position firstPos , Position secondPos) = 0;

	virtual bool SaveGame(const std::string_view path, StorageFormat format) = 0;
	virtual bool LoadGame(const std::string_view path, StorageFormat format) = 0;

	virtual ~IGame() = default;
};

