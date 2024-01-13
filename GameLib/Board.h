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

using BoardPtr = std::shared_ptr<class Board>;

class Board : public IBoard
{
public:
	Board(const uint16_t& size);
	Board(const Board & other);
	~Board();

	uint16_t const GetSize() const override;

	const IColumn* GetElement(const Position& pos) const override;
	const IColumn* GetElement(const uint16_t& row, const uint16_t& column) const override;
	const BridgeVector GetBridgesPositions() const override;
	bool BridgeExists(const Position& firstPos, const Position& secondPos) const override;
	void ComputePathToWin(bool player, bool action, const Position& firstPos, const Position& secondPos);
	bool CheckWinner(bool player) const;

	bool ValidPosibleBridge(const Position& firstPos, const Position& secondPos) const;
	bool ValidPosition(const int16_t& row, const int16_t& column) const;
	bool ValidPlaceColumn(const Position& position) const;
	bool ValidBridge(const Position& firstPos, const Position& secondPos) const;

	bool PlaceColumn(const Position& position, IPlayer* player);
	bool PlaceColumn(const Position& position, IColumn* column);
	uint16_t RemoveColumn(const Position& position);
	bool MakeBridge(const Position& firstPos, const Position& secondPos, IPlayer* player);
	bool RemoveBridge(const Position& firstPos, const Position& secondPos, IPlayer* player);

	void Clear();
    
	
	Board& operator=(const Board& rhs) noexcept;
	const IColumn* operator [](Position pos) const override;
	bool operator==(const Board& rhs) const;

private:
	std::vector<std::string> GetColumnConnections(const Position& position) const;
	bool FindObstacleBridge(const Position& firstPos, const Position& secondPos) const;
	bool Orientation(const Position& A, const Position& B, const Position& C) const;
	bool doIntersect(const Position& A1, const Position& B1, const Position& A2, const Position& B2) const;
	const std::string MakeKey(const Position& firstPos, const Position& secondPos) const;
	const std::pair<Position, Position> ExtractPositionFromKey(const std::string& key) const;
	void MarkPathWithOnes(const Position& startPosition, std::vector<std::vector<bool>>* playerPath);

private:
	std::unordered_map<std::string,Bridge*> m_bridges;
	std::vector<std::vector<IColumn*>> m_matrix;
	std::vector<std::vector<bool>> m_firstPlayerPath;
	std::vector<std::vector<bool>> m_secondPlayerPath;
};