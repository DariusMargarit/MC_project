#include "gtest/gtest.h"

#include "Game.h"

class PlayerTests : public ::testing::Test{

protected:
	void SetUp() override
	{
		m_settings = IGameSettings::GetInstance();
		m_game = IGame::Produce(m_settings);
	}

	void TearDown() override
	{

	}

protected:
	IGameSettingsPtr m_settings;
	IGamePtr m_game;

};

TEST_F(PlayerTests, GetDefaultColorPlayer1Test) {
	// Perform the action

	EColor resultColor = m_game->GetFirstPlayer()->GetColor();

	// Verify the result
	EXPECT_EQ(resultColor, EColor::Blue);
}

TEST_F(PlayerTests, GetDefaultColorPlayer2Test) {
	// Perform the action

	EColor resultColor = m_game->GetSecondPlayer()->GetColor();

	// Verify the result
	EXPECT_EQ(resultColor, EColor::Red);
}

TEST_F(PlayerTests, GetDefaultNamePlayer1Test) {
	// Perform the action
	std::string_view resultName = m_game->GetFirstPlayer()->GetName();

	// Verify the result
	EXPECT_EQ(resultName, "Player1");
}

TEST_F(PlayerTests, GetDefaultNamePlayer2Test) {
	// Perform the action
	std::string_view resultName = m_game->GetSecondPlayer()->GetName();

	// Verify the result
	EXPECT_EQ(resultName, "Player2");
}

TEST_F(PlayerTests, SetColorTest) {
	// Perform the action
	m_game->GetFirstPlayer()->SetColor(EColor::Blue);
	m_game->GetSecondPlayer()->SetColor(EColor::Red);
	// Verify the result
	EXPECT_EQ(m_game->GetFirstPlayer()->GetColor(), EColor::Blue);
	EXPECT_EQ(m_game->GetSecondPlayer()->GetColor(), EColor::Red);
}


TEST_F(PlayerTests, SetNameTest) {
	// Perform the action
	m_game->GetFirstPlayer()->SetName("NewPlayer1Name");
	m_game->GetSecondPlayer()->SetName("NewPlayer2Name");

	// Verify the result
	EXPECT_EQ(m_game->GetFirstPlayer()->GetName(), "NewPlayer1Name");
	EXPECT_EQ(m_game->GetSecondPlayer()->GetName(), "NewPlayer2Name");
}