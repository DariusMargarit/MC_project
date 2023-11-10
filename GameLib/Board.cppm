export module Board;

import <vector>;

export import "Position.h";
export import "IColumn.h";
export import Bridge;

export class Board {
private:
	std::vector<Position*> m_columns;
	std::vector<Bridge*> m_bridges;
	std::vector<std::vector<IColumn*>> m_matrix;
	bool ValidPlaceColumn(Position&) const;
	bool ValidBridge(Position&, Position&) const;
public:
	Board();
	Board(const Board&);
	~Board();
	void PlaceColumn(Position&, const EPlayer&);
	void MakeBridge(Position&, Position&, const EPlayer&);
};