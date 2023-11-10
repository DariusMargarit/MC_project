export module Game;

export import "IGame.h";
export import Board;


export class Game : public IGame
{
public:
	Game(IPlayer* player1, IPlayer* player2);

	IPlayer* GetTurn() const override;

	void PlaceColumn(Position position) override;
	void MakeBridge(Position firstPosition, Position secondPosition) override;
	void RemoveBridge(Position firstPosition, Position secondPosition) override;

	~Game();

private:
	void ChangeTurn();

private:
	Board m_board;
	uint16_t m_columnSize;
	IPlayer* m_player1, *m_player2, *m_turn;
};


