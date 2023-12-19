#include "BulldozerGame.h"

BulldozerGame::BulldozerGame(const BulldozerGame& rhs)
	:m_boardSize{ rhs.m_boardSize }
	{
		m_player1 = new Player(dynamic_cast<Player*>(rhs.m_player1));
		m_player2 = new Player(dynamic_cast<Player*>(rhs.m_player2));
		m_bulldozer = new Player(dynamic_cast<Player*>(rhs.m_bulldozer));
		if (rhs.m_turn == rhs.m_player1)
		{
			m_turn = m_player1;
		}
		else if (rhs.m_turn == rhs.m_player2)
		{
			m_turn = m_player2;
		}
		else if (rhs.m_turn == rhs.m_bulldozer)
		{
			m_turn = m_bulldozer;
		}
		m_board = new Board(*rhs.m_board);
	}

BulldozerGame::~BulldozerGame()
{

	if (m_player1)
		delete m_player1;

	if (m_player2)
		delete m_player2;

	if (m_bulldozer)
		delete m_bulldozer;

	if (m_turn)
		delete m_turn;
	
	if (m_board)
		delete m_board;
}

BulldozerGame& BulldozerGame::operator=(const BulldozerGame& rhs)
{
	if (this != &rhs) {

		delete m_player1;
		delete m_player2;
		delete m_bulldozer;
		delete m_board;

		m_boardSize = rhs.m_boardSize;
		m_player1 = new Player(dynamic_cast<Player*>(rhs.m_player1));
		m_player2 = new Player(dynamic_cast<Player*>(rhs.m_player2));
		m_bulldozer = new Player(dynamic_cast<Player*>(rhs.m_bulldozer));
		if (rhs.m_turn == rhs.m_player1)
		{
			m_turn = m_player1;
		}
		else if (rhs.m_turn == rhs.m_player2)
		{
			m_turn = m_player2;
		}
		else if (rhs.m_turn == rhs.m_bulldozer)
		{
			m_turn = m_bulldozer;
		}
		m_board = new Board(*rhs.m_board);

	}
	return *this;
}



