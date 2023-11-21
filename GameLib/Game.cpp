module Game;

Game::Game(IPlayer* player1, IPlayer* player2, uint16_t boardSize)
	: m_player1(player1)
	, m_player2(player2)
	, m_turn(player1)
	, m_boardSize(boardSize)
	, m_board(new Board(boardSize))
{
	// Empty
}

Game::~Game()
{
	// Empty
}

void Game::PlaceColumn(Position position)
{
	if (m_turn->GetColor() == "RED") 
	{
		if (position.GetY() < 1 || position.GetY() > m_boardSize - 2) 
		{
			// exception
			return;
		}
	}
	else 
	{
		if (position.GetX() < 1 || position.GetX() > m_boardSize - 2)
		{
			// exception
			return;
		}
	}
	m_board->PlaceColumn(position, m_turn);

	ChangeTurn();
}

void Game::MakeBridge(Position firstPosition, Position secondPosition)
{
	m_board->MakeBridge(firstPosition, secondPosition, m_turn);
}

void Game::RemoveBridge(Position firstPosition, Position secondPosition)
{
	m_board->RemoveBridge(firstPosition, secondPosition, m_turn);
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