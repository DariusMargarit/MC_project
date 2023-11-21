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

Game::Game(const Game& otherGame)
	:m_boardSize{otherGame.m_boardSize}
{
	m_player1 = new Player(dynamic_cast<Player*>(otherGame.m_player1));
	m_player2 = new Player(dynamic_cast<Player*>(otherGame.m_player2));
	m_turn = (otherGame.m_turn == otherGame.m_player1) ? m_player1 : m_player2;
	m_board = new Board(*otherGame.m_board);

}

Game::~Game()
{
	// Empty
}

void Game::PlaceColumn(Position position)
{
	if (m_turn == m_player1) 
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

Game& Game::operator=(const Game& otherGame)
{
	if (this != &otherGame) {
		
		delete m_player1;
		delete m_player2;
		delete m_board;

		m_boardSize = otherGame.m_boardSize;
		m_player1 = new Player(dynamic_cast<Player*>(otherGame.m_player1));
		m_player2 = new Player(dynamic_cast<Player*>(otherGame.m_player2));
		m_turn = (otherGame.m_turn == otherGame.m_player1) ? m_player1 : m_player2;
		m_board = new Board(*otherGame.m_board);

	}
	return *this;
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