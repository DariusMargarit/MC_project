#include "Game.h"
#include <ranges>
#include <algorithm>


Game::Game(const IGameSettings& settings)
	: m_player1{ new Player(settings.GetFirstPlayerName(), settings.GetFirstPlayerColor()) }
	, m_player2{ new Player(settings.GetSecondPlayerName(), settings.GetSecondPlayerColor()) }
	, m_boardSize{ settings.GetTableSize() }
	, m_parser{ parser::ITwixtParser::Produce(settings.GetTableSize())}
{	
	m_board = new Board(m_boardSize);
	m_turn = m_player1;
}

Game::Game(const Game& rhs)
	: m_boardSize{rhs.m_boardSize}
{
	m_player1 = new Player(dynamic_cast<Player*>(rhs.m_player1));
	m_player2 = new Player(dynamic_cast<Player*>(rhs.m_player2));
	m_turn = (rhs.m_turn == rhs.m_player1) ? m_player1 : m_player2;
	m_board = new Board(*rhs.m_board);
}

Game::Game(Game&& rhs) noexcept
	: m_boardSize{ rhs.m_boardSize }
 {
	m_player1 = new Player(dynamic_cast<Player*>(rhs.m_player1));
	m_player2 = new Player(dynamic_cast<Player*>(rhs.m_player2));
	m_turn = (rhs.m_turn == rhs.m_player1) ? m_player1 : m_player2;
	m_board = new Board(*rhs.m_board);

	rhs.m_board = nullptr;
	rhs.m_boardSize = 0;
	rhs.m_player1 = nullptr;
	rhs.m_player2 = nullptr;
	rhs.m_turn = nullptr;
}

void Game::PlaceColumn(Position position)
{
	if ((position.GetColumn() == 0 || position.GetColumn() == m_board->GetSize() - 1))
	{
		if (m_turn == m_player2)
		{
			if (m_board->PlaceColumn(position, m_turn))
			{
				NotifyPlaceColumn(position, m_turn);
				ChangeTurn();
			}
		}
		   
	}
	else if ((position.GetRow() == 0 || position.GetRow() == m_board->GetSize() - 1) )
	{
		if (m_turn == m_player1)
		{
			if (m_board->PlaceColumn(position, m_turn))
			{
				NotifyPlaceColumn(position, m_turn);
				ChangeTurn();
			}
		}
	}
	else
	{
		if (m_board->PlaceColumn(position, m_turn))
		{
			NotifyPlaceColumn(position, m_turn);
			ChangeTurn();
		}
	}

}

void Game::MakeBridge(Position lhs, Position rhs)
{
	if(m_board->MakeBridge(lhs, rhs, m_turn))
	{
		NotifyMakeBridge(lhs, rhs, m_turn);
		ComputePathToWin(0, lhs, rhs);
	}
}

void Game::RemoveBridge(Position lhs, Position rhs)
{
	if(m_board->RemoveBridge(lhs, rhs, m_turn))
	{
		NotifyRemoveBridge(lhs, rhs, m_turn);
		ComputePathToWin(1, lhs, rhs);
	}
}

void Game::SwapPlayers()
{
	EColor auxiliarColor = m_player1->GetColor();
	m_player1->SetColor(m_player2->GetColor());
	m_player2->SetColor(auxiliarColor);
	ChangeTurn();
}

IPlayer* Game::GetFirstPlayer() const
{
	return m_player1;
}

IPlayer* Game::GetSecondPlayer() const
{
	return m_player2;
}

Game& Game::operator=(const Game& rhs)
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

Game& Game::operator=(Game&& rhs) noexcept {
	if (this == &rhs)
	{
		return *this;
	}
		delete m_player1;
		delete m_player2;
		delete m_board;

		m_boardSize = rhs.m_boardSize;
		m_player1 = new Player(dynamic_cast<Player*>(rhs.m_player1));
		m_player2 = new Player(dynamic_cast<Player*>(rhs.m_player2));
		m_turn = (rhs.m_turn == rhs.m_player1) ? m_player1 : m_player2;
		m_board = new Board(*rhs.m_board);

		rhs.m_board = nullptr;
		rhs.m_boardSize = 0;
	    rhs.m_player1 = nullptr;
	    rhs.m_player2 = nullptr;
	    rhs.m_turn = nullptr;

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

IPlayer* Game::CheckWinner() const
{
	if (m_turn == m_player1)
	{
		if (m_board->CheckWinner(0))
		{
			return m_player1;
		}
	}
	else
	{
		if (m_board->CheckWinner(1))
		{
			return m_player2;
		}
	}
	return nullptr;
}

void Game::AddObserver(ObserverPtr observer)
{
	m_observers.push_front(observer);
}

void Game::RemoveObserver(ObserverPtr observer)
{
	m_observers.remove_if(
		[observer](ObserverPtr weakObserver) {
			return weakObserver.expired() || weakObserver.lock() == observer.lock();
		});
}

void Game::NotifyPlaceColumn(Position position, IPlayer* player) const
{
	for (auto& observer : m_observers)
	{
		observer.lock()->OnColumnPlaced(position, player);
	}
}

void Game::NotifyMakeBridge(Position lhs, Position rhs, IPlayer* player) const
{
	for (auto& observer : m_observers)
	{
		observer.lock()->OnBridgePlaced(lhs, rhs, player);
	}
}

void Game::NotifyRemoveBridge(Position lhs, Position rhs, IPlayer* player) const
{
	for (auto& observer : m_observers)
	{
		observer.lock()->OnBridgeRemoved(lhs, rhs, player);
	}
}

void Game::ChangeTurn()
{
	m_turn = m_turn == m_player1 ? m_player2 : m_player1;
}

void Game::ComputePathToWin(bool action, Position& lhs, Position& rhs) const
{
	if (m_turn == m_player1)
	{
		m_board->ComputePathToWin(0, action, lhs, rhs);
	}
	else
	{
		m_board->ComputePathToWin(1, action, lhs, rhs);
	}
}

IGamePtr IGame::Produce(const IGameSettings& settings)
{
	return std::make_shared<Game>(settings);
}