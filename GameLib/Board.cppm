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

	const IColumn* GetElement(Position pos) const override;
	const uint16_t GetSize() const override;


	void PlaceColumn(Position& position, IPlayer* player);
	void MakeBridge(Position& firstPosition, Position& secondPosition, IPlayer* player);
	void RemoveBridge(Position& firstPosition, Position& secondPosition, IPlayer* player);

	const IColumn* operator [](Position pos) const override;

private:
	bool ValidPlaceColumn(Position position) const;
	bool ValidBridge(Position firstPosition, Position secondPosition) const;

private:
	std::vector<Bridge*> m_bridges;
	std::vector<std::vector<IColumn*>> m_matrix;
};