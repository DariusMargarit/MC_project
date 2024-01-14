#include "gtest/gtest.h"

#include "Game.h"

class GameTests : public ::testing::Test {

protected:
	void SetUp() override
	{
		m_settings = IGameSettings::GetInstance();
		m_game = std::make_shared<Game>(m_settings);
	}

	void TearDown() override
	{

	}

protected:
	IGameSettingsPtr m_settings;
	GamePtr m_game;

};

// Test fixture for testing specific methods
TEST_F(GameTests, GetTurnReturnsValidPlayer) {

	IPlayerPtr turn = m_game->GetTurn();
	EXPECT_NE(turn, nullptr);
	// Add more assertions or validations based on your requirements
}

TEST_F(GameTests, SwapTest) {

	std::string firstPlayerName = m_game->GetFirstPlayer()->GetName().data();
	std::string secondPlayerName = m_game->GetSecondPlayer()->GetName().data();
	m_game->SwapPlayers();
	std::string newFirstPlayer = m_game->GetFirstPlayer()->GetName().data();
	std::string newSecondPlayer = m_game->GetSecondPlayer()->GetName().data();

	EXPECT_EQ(firstPlayerName, newSecondPlayer);
	EXPECT_EQ(secondPlayerName, newFirstPlayer);
}

TEST_F(GameTests, FirstPlayerBase1Test) {

	// the position should be valid before insertion
	IPlayerPtr turn = m_game->GetTurn();

	if (m_game->GetFirstPlayer() == turn)
	{
		EXPECT_EQ(m_game->PlaceColumn(Position(0, 1)), true);
		// get the inserted column
		auto insertedColumn = m_game->GetBoard()->GetElement(Position(0, 1));

		// expects that a column was inserted at Position(0, 1)
		EXPECT_TRUE(insertedColumn != nullptr);

		// expects that the found column is owned by Player1
		EXPECT_EQ(insertedColumn->GetPlayer(), m_game->GetFirstPlayer());

	}
	else if (m_game->GetSecondPlayer() == turn)
	{
		EXPECT_EQ(m_game->PlaceColumn(Position(0, 1)), false);


	}

}

TEST_F(GameTests, FirstPlayerBase2Test) {

	// the position should be valid before insertion
	IPlayerPtr turn = m_game->GetTurn();

	if (m_game->GetFirstPlayer() == turn)
	{
		EXPECT_EQ(m_game->PlaceColumn(Position(23, 1)), true);
		// get the inserted column
		auto insertedColumn = m_game->GetBoard()->GetElement(Position(23, 1));

		// expects that a column was inserted at Position(23, 1)
		EXPECT_TRUE(insertedColumn != nullptr);

		// expects that the found column is owned by Player1
		EXPECT_EQ(insertedColumn->GetPlayer(), m_game->GetFirstPlayer());

	}
	else if (m_game->GetSecondPlayer() == turn)
	{
		EXPECT_EQ(m_game->PlaceColumn(Position(23, 1)), false);


	}

}
TEST_F(GameTests, SecondPlayerBase1Test) {

	// the position should be valid before insertion
	IPlayerPtr turn = m_game->GetTurn();

	if (m_game->GetFirstPlayer() == turn)
	{
		EXPECT_EQ(m_game->PlaceColumn(Position(1, 0)), false);


	}
	else if (m_game->GetSecondPlayer() == turn)
	{
		EXPECT_EQ(m_game->PlaceColumn(Position(1, 0)), true);

		// get the inserted column
		auto insertedColumn = m_game->GetBoard()->GetElement(Position(1, 0));

		// expects that a column was inserted at Position(1, 0)
		EXPECT_TRUE(insertedColumn != nullptr);

		// expects that the found column is owned by Player
		EXPECT_EQ(insertedColumn->GetPlayer(), m_game->GetSecondPlayer());
	}

}

TEST_F(GameTests, SecondPlayerBase2Test) {

	// the position should be valid before insertion
	IPlayerPtr turn = m_game->GetTurn();

	if (m_game->GetFirstPlayer() == turn)
	{
		EXPECT_EQ(m_game->PlaceColumn(Position(1, 23)), false);


	}
	else if (m_game->GetSecondPlayer() == turn)
	{
		EXPECT_EQ(m_game->PlaceColumn(Position(1, 23)), true);

		// get the inserted column
		auto insertedColumn = m_game->GetBoard()->GetElement(Position(1, 23));

		// expects that a column was inserted at Position(1, 23)
		EXPECT_TRUE(insertedColumn != nullptr);

		// expects that the found column is owned by Player2
		EXPECT_EQ(insertedColumn->GetPlayer(), m_game->GetSecondPlayer());
	}

}