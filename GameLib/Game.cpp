module Game;

Game::~Game()
{
}

void Game::PlaceColumn(Position position)
{
	m_board.PlaceColumn(position, m_turn);
}

void Game::MakeBridge(Position firstPosition, Position secondPosition)
{

}

void Game::RemoveBridge(Position firstPosition, Position secondPosition)
{

}