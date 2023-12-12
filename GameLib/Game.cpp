#include "Game.h"
#include <ranges>
#include <algorithm>


Game::Game(const IGameSettings& settings)
	: m_player1{ new Player(settings.GetFirstPlayerName(), settings.GetFirstPlayerColor()) }
	, m_player2{ new Player(settings.GetSecondPlayerName(), settings.GetSecondPlayerColor()) }
	, m_boardSize{ settings.GetTableSize() }
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

void Game::MakeBridge(Position firstPosition, Position secondPosition)
{
	if(m_board->MakeBridge(firstPosition, secondPosition, m_turn))
	{
		NotifyMakeBridge(firstPosition, secondPosition, m_turn);
		ComputePathToWin(0, firstPosition, secondPosition);
	}
}

void Game::RemoveBridge(Position firstPosition, Position secondPosition)
{
	if(m_board->RemoveBridge(firstPosition, secondPosition, m_turn))
	{
		NotifyRemoveBridge(firstPosition, secondPosition, m_turn);
		ComputePathToWin(1, firstPosition, secondPosition);
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

void Game::NotifyMakeBridge(Position firstPosition, Position secondPosition, IPlayer* player) const
{
	for (auto& observer : m_observers)
	{
		observer.lock()->OnBridgePlaced(firstPosition, secondPosition, player);
	}
}

void Game::NotifyRemoveBridge(Position firstPosition, Position secondPosition, IPlayer* player) const
{
	for (auto& observer : m_observers)
	{
		observer.lock()->OnBridgeRemoved(firstPosition, secondPosition, player);
	}
}

void Game::ChangeTurn()
{
	m_turn = m_turn == m_player1 ? m_player2 : m_player1;
}

void Game::ComputePathToWin(bool action, Position& firstPosition, Position& secondPosition) const
{
	if (m_turn == m_player1)
	{
		m_board->ComputePathToWin(0, action, firstPosition, secondPosition);
	}
	else
	{
		m_board->ComputePathToWin(1, action, firstPosition, secondPosition);
	}
}

IGamePtr IGame::Produce(const IGameSettings& settings)
{
	return std::make_shared<Game>(settings);
}