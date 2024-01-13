#include "BulldozerGame.h"
#include <random>

BulldozerGame::BulldozerGame(BoardPtr& board)
	: m_board{ board }
	, m_epsilon{0.99}
	, m_currentPosition{ {0,0} }
{
	// Empty
}

bool BulldozerGame::CoinFlip()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	return dis(gen) > m_epsilon;
	
}

void BulldozerGame::DestroyRandomColumn(PlayerPtr firstPlayer, PlayerPtr secondPlayer)
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<uint16_t> distribution(0, m_board->GetSize() - 1);

	uint16_t randomRowIndex{ distribution(gen) };
	uint16_t randomColumnIndex{ distribution(gen) };
	Position position{ randomRowIndex ,randomRowIndex };

	while (m_board->GetElement(position) == nullptr)
	{
		randomRowIndex = distribution(gen);
		randomColumnIndex = distribution(gen);
		position = { randomRowIndex ,randomColumnIndex };
	}

	uint16_t numberOfBridgesRemoved = m_board->RemoveColumn(position);

	if (numberOfBridgesRemoved)
	{
		PlayerPtr playerUsed = m_board->GetElement(position)->GetPlayer() == firstPlayer
			? firstPlayer : secondPlayer;
		playerUsed->IncreaseBridgeNumber(numberOfBridgesRemoved);
		playerUsed->IncreaseColumnNumber();
	}
	PlaceBulldozer(position);
	numberOfBridgesRemoved = m_board->RemoveColumn(m_currentPosition);
	m_currentPosition = position;

}

void BulldozerGame::MoveToRandomEmptyPlace()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<uint16_t> distribution(0, m_board->GetSize() - 1);

	uint16_t randomRowIndex{ distribution(gen) };
	uint16_t randomColumnIndex{ distribution(gen) };
	Position position{ randomRowIndex ,randomRowIndex };

	while (m_board->GetElement(position) != nullptr)
	{
		randomRowIndex = distribution(gen);
		randomColumnIndex = distribution(gen);
		position = { randomRowIndex ,randomColumnIndex };
	}
	PlaceBulldozer(position);
	uint16_t numberOfBridgesRemoved = m_board->RemoveColumn(m_currentPosition);
	m_currentPosition = position;

}

void BulldozerGame::DestroyOrMove(PlayerPtr firstPlayer, PlayerPtr secondPlayer)
{
	if (CoinFlip())
	{
		DestroyRandomColumn(firstPlayer, secondPlayer);
	}
	else
	{
		m_epsilon *= 0.97;
		MoveToRandomEmptyPlace();
	}


}

void BulldozerGame::PlaceBulldozer(const Position& position)
{
	m_board->PlaceColumn(position, std::make_shared<BulldozerColumn>());
}

