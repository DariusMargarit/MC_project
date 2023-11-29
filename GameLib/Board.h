#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

#include "Position.h"
#include "IColumn.h"
#include "IBoard.h"
#include "Bridge.h"

class Board : public IBoard
{
public:
	Board(uint16_t size);
	Board(const Board& otherBoard);
	~Board();

	const IColumn* GetElement(const Position& pos) const override;
	const IColumn* GetElement(const uint16_t& row, const uint16_t& column) const override;
	const uint16_t GetSize() const override;


	void PlaceColumn(Position& position, IPlayer* player);
	void MakeBridge(Position& firstPosition, Position& secondPosition, IPlayer* player);
	void RemoveBridge(Position& firstPosition, Position& secondPosition, IPlayer* player);

	const IColumn* operator [](Position pos) const override;

private:
	bool ValidPlaceColumn(Position position) const;
	std::vector<std::vector<IColumn*>> BridgeSurroundingMatrix(Position& firstPosition, Position& secondPosition) const;
	bool FindObstacleBridge(Position& bridge1FirstPosition, Position& bridge1SecondPosition) const;
	bool orientation(Position& A, Position& B, Position& C) const;
	bool doIntersect(Position& A1, Position& B1, Position& A2, Position& B2) const;
	bool ValidBridge(Position& firstPosition, Position& secondPosition) const;
	const std::string MakeKey(const Position& firstPosition, const Position& secondPosition) const;
	const std::pair<Position, Position> ExtractPositionFromKey(const std::string& key);

private:
	std::unordered_map<std::string,Bridge*> m_bridges;
	std::vector<std::vector<IColumn*>> m_matrix;
};