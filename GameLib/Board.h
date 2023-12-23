#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <stack>
#include <array>

#include "Position.h"
#include "IColumn.h"
#include "IBoard.h"
#include "Bridge.h"
#include "../TwixtTextParser/ITwixtParser.h"

class Board : public IBoard
{
public:
	Board(const uint16_t& size);
	Board(const Board & other);
	~Board();

	const uint16_t GetSize() const override;

	const IColumn* GetElement(const Position& pos) const override;
	const IColumn* GetElement(const uint16_t& row, const uint16_t& column) const override;
	const BridgeVector GetBridgesPositions() const override;
	bool BridgeExists(const Position& firstPos, const Position& secondPos) const override;

	bool PlaceColumn(const Position& position, IPlayer* player);
	void PlaceMine(const Position& position);
	bool MakeBridge(const Position& firstPos, const Position& secondPos, IPlayer* player);
	bool RemoveBridge(const Position& firstPos, const Position& secondPos, IPlayer* player);
	void ComputePathToWin(bool player, bool action, Position& firstPos, Position& secondPos);
	bool CheckWinner(bool player);
	void AddMines();
    

	const IColumn* operator [](Position pos) const override;
	bool operator==(const Board& rhs) const;

private:
	bool ValidPosition(const int16_t& row, const int16_t& column) const;
	bool ValidPlaceColumn(const Position& position) const;
	bool FindObstacleBridge(const Position& firstPos, const Position& secondPos) const;
	bool Orientation(const Position& A, const Position& B, const Position& C) const;
	bool doIntersect(const Position& A1, const Position& B1, const Position& A2, const Position& B2) const;
	bool ValidBridge(const Position& firstPos, const Position& secondPos) const;
	const std::string MakeKey(const Position& firstPos, const Position& secondPos) const;
	const std::pair<Position, Position> ExtractPositionFromKey(const std::string& key) const;
	void MarkPathWithOnes(Position& startPosition, std::vector<std::vector<bool>>* playerPath);

private:
	std::unordered_map<std::string,Bridge*> m_bridges;
	std::vector<std::vector<IColumn*>> m_matrix;
	std::vector<std::vector<bool>> m_firstPlayerPath;
	std::vector<std::vector<bool>> m_secondPlayerPath;
};