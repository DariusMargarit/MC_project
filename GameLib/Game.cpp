module Game;

Game::Game(IPlayer* player1, IPlayer* player2, uint16_t boardSize)
	: m_player1(player1)
	, m_player2(player2)
	, m_turn(player1)
	, m_board(new Board(boardSize))
{
	
}

Game::~Game()
{

}

void Game::PlaceColumn(Position position)
{
	m_board->PlaceColumn(position, m_turn);

	ChangeTurn();
}

void Game::MakeBridge(Position firstPosition, Position secondPosition)
{
	m_board->MakeBridge(firstPosition, secondPosition, m_turn);
}

void Game::RemoveBridge(Position firstPosition, Position secondPosition)
{

}

IPlayer* Game::GetTurn() const 
{
	return m_turn;
}

IBoard* Game::GetBoard() const 
{
	return m_board;
}

void Game::ChangeTurn()
{
	m_turn = m_turn == m_player1 ? m_player2 : m_player1;
}

IGame* IGame::Produce(IPlayer* player1, IPlayer* player2, uint16_t boardSize)
{
	return new Game(player1, player2, boardSize);
}