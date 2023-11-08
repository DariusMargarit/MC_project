export module Game;

export import IGame;
export import Board;

export class Game : public IGame {
private:
	Board m_board;
	uint16_t m_columnSize;
	EPlayer m_turn;


public:
	void PlaceColumn(Position position) override;
	void MakeBridge(Position firstPosition, Position secondPosition) override;
	void RemoveBridge(Position firstPosition, Position secondPosition) override;
	~Game();

};

