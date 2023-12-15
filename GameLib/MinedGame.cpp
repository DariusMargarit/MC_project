#include "MinedGame.h"

MinedGame::MinedGame(const IGameSettings& settings)
	: m_player1{ new Player(settings.GetFirstPlayerName(), settings.GetFirstPlayerColor()) }
	, m_player2{ new Player(settings.GetSecondPlayerName(), settings.GetSecondPlayerColor()) }
	, m_boardSize{ settings.GetTableSize() }
{
	m_board = new Board(m_boardSize);
	m_turn = m_player1;
	m_board->AddMines();
}

MinedGame::MinedGame(const MinedGame& rhs)
	:m_boardSize{ rhs.m_boardSize }
{
	m_player1 = new Player(dynamic_cast<Player*>(rhs.m_player1));
	m_player2 = new Player(dynamic_cast<Player*>(rhs.m_player2));
	m_turn = (rhs.m_turn == rhs.m_player1) ? m_player1 : m_player2;
	m_board = new Board(*rhs.m_board);
}

MinedGame::~MinedGame()
{
	if(m_player1)
		delete m_player1;

	if(m_player2)
		delete m_player2;

	if (m_turn)
		delete m_turn;

	if (m_board)
		delete m_board;
}

MinedGame& MinedGame::operator=(const MinedGame& rhs)
{
	if (this != &rhs) {

		delete m_player1;
		delete m_player2;
		delete m_board;

		m_boardSize = rhs.m_boardSize;
		m_player1 = new Player(dynamic_cast<Player*>(rhs.m_player1));
		m_player2 = new Player(dynamic_cast<Player*>(rhs.m_player2));
		m_turn = (rhs.m_turn == rhs.m_player1) ? m_player1 : m_player2;
		m_board = new Board(*rhs.m_board);

	}
	return *this;
}
