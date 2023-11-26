#include "Game.h"

Game::Game(const IGameSettings& settings)
	: m_player1(new Player(settings.GetFirstPlayerName(), settings.GetFirstPlayerColor()))
	, m_player2(new Player(settings.GetSecondPlayerName(), settings.GetSecondPlayerColor()))
	, m_boardSize(settings.GetTableSize())
{
	m_board = new Board(m_boardSize);
	m_turn = m_player1;
}

Game::Game(const Game& otherGame)
	:m_boardSize{otherGame.m_boardSize}
{
	m_player1 = new Player(dynamic_cast<Player*>(otherGame.m_player1));
	m_player2 = new Player(dynamic_cast<Player*>(otherGame.m_player2));
	m_turn = (otherGame.m_turn == otherGame.m_player1) ? m_player1 : m_player2;
	m_board = new Board(*otherGame.m_board);
}

Game::Game(Game&& otherGame) noexcept
	: m_boardSize{ otherGame.m_boardSize }
 {
	m_player1 = new Player(dynamic_cast<Player*>(otherGame.m_player1));
	m_player2 = new Player(dynamic_cast<Player*>(otherGame.m_player2));
	m_turn = (otherGame.m_turn == otherGame.m_player1) ? m_player1 : m_player2;
	m_board = new Board(*otherGame.m_board);

	otherGame.m_board = nullptr;
	otherGame.m_boardSize = 0;
	otherGame.m_player1 = nullptr;
	otherGame.m_player2 = nullptr;
	otherGame.m_turn = nullptr;
}
Game::~Game()
{
	// Empty
}

void Game::PlaceColumn(Position position)
{
	// Code needs review and to be placed in a validation function
	
	//if (m_turn == m_player1) 
	//{
	//	if (position.GetY() < 1 || position.GetY() > m_boardSize - 2) 
	//	{
	//		// exception
	//		return;
	//	}
	//}
	//else 
	//{
	//	if (position.GetX() < 1 || position.GetX() > m_boardSize - 2)
	//	{
	//		// exception
	//		return;
	//	}
	//}


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

Game& Game::operator=(Game&& otherGame) noexcept {
	if (this == &otherGame)
	{
		return *this;
	}
		delete m_player1;
		delete m_player2;
		delete m_board;

		m_boardSize = otherGame.m_boardSize;
		m_player1 = new Player(dynamic_cast<Player*>(otherGame.m_player1));
		m_player2 = new Player(dynamic_cast<Player*>(otherGame.m_player2));
		m_turn = (otherGame.m_turn == otherGame.m_player1) ? m_player1 : m_player2;
		m_board = new Board(*otherGame.m_board);

		otherGame.m_board = nullptr;
		otherGame.m_boardSize = 0;
	    otherGame.m_player1 = nullptr;
	    otherGame.m_player2 = nullptr;
	    otherGame.m_turn = nullptr;

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

IGame* IGame::Produce(const IGameSettings& settings)
{
	return new Game(settings);
}