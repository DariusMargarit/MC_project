module Game;

Game::Game(IPlayer* player1, IPlayer* player2) 
	: m_player1(player1)
	, m_player2(player2)
	, m_turn(player1)
{
	
}

Game::~Game()
{

}

void Game::PlaceColumn(Position position)
{
	m_board.PlaceColumn(position, m_turn);

	ChangeTurn();
}

void Game::MakeBridge(Position firstPosition, Position secondPosition)
{
	m_board.MakeBridge(firstPosition, secondPosition, m_turn);
}

void Game::RemoveBridge(Position firstPosition, Position secondPosition)
{

}

IPlayer* Game::GetTurn() const {
	return m_turn;
}

void Game::ChangeTurn()
{
	m_turn = m_turn == m_player1 ? m_player2 : m_player1;
}

IGame* IGame::Produce(IPlayer* player1, IPlayer* player2)
{
	return new Game(player1, player2);
}