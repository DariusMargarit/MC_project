#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <stack>

#include "Position.h"
#include "IColumn.h"
#include "IBoard.h"
#include "Bridge.h"

class Board : public IBoard
{
public:
	Board(const uint16_t& size);
	Board(const Board& otherBoard);
	~Board();

	const uint16_t GetSize() const override;

	const IColumn* GetElement(const Position& pos) const override;
	const IColumn* GetElement(const uint16_t& row, const uint16_t& column) const override;
	const BridgeVector GetBridgesPositions() const override;
	bool BridgeExists(const Position& firstPosition, const Position& secondPosition) const override;

	bool PlaceColumn(Position& position, IPlayer* player);
	void MakeBridge(Position& firstPosition, Position& secondPosition, IPlayer* player);
	void RemoveBridge(Position& firstPosition, Position& secondPosition, IPlayer* player);
	void ComputePathToWin(bool player, bool action, Position& firstPosition, Position& secondPosition);
	bool CheckWinner(bool player);

	const IColumn* operator [](Position pos) const override;





private:
	bool ValidPlaceColumn(const Position& position) const;
	bool FindObstacleBridge(Position& bridge1FirstPosition, Position& bridge1SecondPosition) const;
	bool orientation(Position& A, Position& B, Position& C) const;
	bool doIntersect(Position& A1, Position& B1, Position& A2, Position& B2) const;
	bool ValidBridge(Position& firstPosition, Position& secondPosition) const;
	const std::string MakeKey(const Position& firstPosition, const Position& secondPosition) const;
	const std::pair<Position, Position> ExtractPositionFromKey(const std::string& key);
	void MarkPathWithOnes(Position& startPosition, std::vector<std::vector<bool>>* playerPath);

private:
	std::unordered_map<std::string,Bridge*> m_bridges;
	std::vector<std::vector<IColumn*>> m_matrix;
	std::vector<std::vector<bool>> m_firstPlayerPath;
	std::vector<std::vector<bool>> m_secondPlayerPath;
};