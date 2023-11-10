export module Board;

import <vector>;

export import "Position.h";
export import "IColumn.h";
export import Bridge;

export class Board 
{
public:
	Board() = default;
	Board(const Board& otherBoard);
	~Board();

	void PlaceColumn(Position& position, IPlayer* player);
	void MakeBridge(Position& firstPosition, Position& secondPosition, IPlayer* player);

private:
	bool ValidPlaceColumn(Position&) const;
	bool ValidBridge(Position&, Position&) const;

private:
	std::vector<Position*> m_columns;
	std::vector<Bridge*> m_bridges;
	std::vector<std::vector<IColumn*>> m_matrix;
};