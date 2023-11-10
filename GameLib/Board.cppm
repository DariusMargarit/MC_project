export module Board;

import <vector>;

export import "Position.h";
export import "IColumn.h";
export import "IBoard.h";
export import Bridge;

export class Board : public IBoard
{
public:
	Board(uint16_t size);
	Board(const Board& otherBoard);
	~Board();

	IColumn* GetElement(Position pos) const override;
	void PlaceColumn(Position& position, IPlayer* player);
	void MakeBridge(Position& firstPosition, Position& secondPosition, IPlayer* player);



private:
	bool ValidPlaceColumn(Position position) const;
	bool ValidBridge(Position firstPosition, Position secondPosition) const;

private:
	std::vector<Position*> m_columns;
	std::vector<Bridge*> m_bridges;
	std::vector<std::vector<IColumn*>> m_matrix;
};